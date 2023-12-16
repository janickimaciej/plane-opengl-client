#include "app/threads/physics_thread.hpp"

#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/udp/udp_communication.hpp"
#include "common/airplane_info.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/notification.hpp"
#include "physics/player_input.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"
#include "physics/timestep.hpp"

#include <semaphore>
#include <thread>

namespace App
{
	PhysicsThread::PhysicsThread(ExitSignal& exitSignal, GameMode gameMode,
		std::binary_semaphore& renderingSemaphore, const Physics::SimulationClock& simulationClock,
		Physics::SimulationBuffer& simulationBuffer, int ownId, Physics::Notification& notification,
		Graphics::RenderingBuffer& renderingBuffer, OwnInput& ownInput,
		UDPCommunication* udpCommunication) :
		m_exitSignal{exitSignal},
		m_gameMode{gameMode},
		m_simulationClock{simulationClock},
		m_simulationBuffer{simulationBuffer},
		m_notification{notification},
		m_ownId{ownId},
		m_renderingBuffer{renderingBuffer},
		m_ownInput{ownInput},
		m_udpCommunication{udpCommunication},
		m_thread
		{
			[this, &renderingSemaphore]
			{ 
				this->start(renderingSemaphore);
			}
		}
	{ }

	void PhysicsThread::join()
	{
		m_thread.join();
	}

	void PhysicsThread::start(std::binary_semaphore& renderingSemaphore)
	{
		Physics::Timestep initialTimestep{};

		m_notification.forceGetNotification(initialTimestep);
		
		m_simulationBuffer.setOwnInput(initialTimestep, Physics::PlayerInput{});
		m_simulationBuffer.update(initialTimestep);

		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos =
			m_simulationBuffer.getAirplaneInfos(initialTimestep);
		m_renderingBuffer.updateBuffer(std::move(airplaneInfos));

		renderingSemaphore.release();
		mainLoop(initialTimestep);
	}

	void PhysicsThread::mainLoop(const Physics::Timestep& initialTimestep)
	{
		Physics::Timestep timestep = initialTimestep;
		while(!m_exitSignal.shouldStop())
		{
			timestep = timestep.next();
			m_notification.getNotification(timestep);
			sleepIfFuture(timestep);

			Physics::PlayerInput ownInput = m_ownInput.getOwnInput();
			bool inputSet = m_simulationBuffer.setOwnInput(timestep, ownInput);
			m_simulationBuffer.update(timestep);

			std::unordered_map<int, Common::AirplaneInfo> airplaneInfos =
				m_simulationBuffer.getAirplaneInfos(timestep);
			m_renderingBuffer.updateBuffer(std::move(airplaneInfos));

			if (m_gameMode == GameMode::multiplayer && inputSet)
			{
				m_udpCommunication->sendControlFrame(timestep, m_ownId, ownInput);
			}
		}
	}

	void PhysicsThread::sleepIfFuture(const Physics::Timestep& timestep)
	{
		Physics::Timestep currentTimestep = m_simulationClock.getTime();
		while (currentTimestep < timestep)
		{
			currentTimestep = m_simulationClock.getTime();
		}
	}
};
