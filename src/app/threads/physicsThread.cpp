#include "app/threads/physicsThread.hpp"

#include "app/exitSignal.hpp"
#include "app/gameMode.hpp"
#include "app/ownInput.hpp"
#include "app/udp/udpCommunication.hpp"
#include "common/sceneInfo.hpp"
#include "graphics/renderingBuffer.hpp"
#include "physics/notification.hpp"
#include "physics/playerInput.hpp"
#include "physics/simulationBuffer.hpp"
#include "physics/simulationClock.hpp"
#include "physics/timestep.hpp"

#include <memory>
#include <semaphore>
#include <thread>

namespace App
{
	PhysicsThread::PhysicsThread(ExitSignal& exitSignal, GameMode gameMode,
		const Physics::SimulationClock& simulationClock,
		Physics::SimulationBuffer& simulationBuffer, int ownId, Physics::Notification& notification,
		Graphics::RenderingBuffer& renderingBuffer, OwnInput& ownInput,
		UDPCommunication* udpCommunication,
		const std::shared_ptr<std::binary_semaphore>& renderingThreadSemaphore) :
		m_exitSignal{exitSignal},
		m_gameMode{gameMode},
		m_simulationClock{simulationClock},
		m_simulationBuffer{simulationBuffer},
		m_notification{notification},
		m_ownId{ownId},
		m_renderingBuffer{renderingBuffer},
		m_ownInput{ownInput},
		m_udpCommunication{udpCommunication}
	{
		m_thread = std::thread(
			[this, renderingThreadSemaphore]
			{
				this->start(std::move(renderingThreadSemaphore));
			});
	}

	void PhysicsThread::join()
	{
		m_thread.join();
	}

	void PhysicsThread::start(std::shared_ptr<std::binary_semaphore> renderingThreadSemaphore)
	{
		Physics::Timestep initialTimestep{};

		m_notification.forceGetNotification(initialTimestep);
		
		m_simulationBuffer.writeControlFrame(initialTimestep, m_ownId, Physics::PlayerInput{});
		m_simulationBuffer.update(initialTimestep);

		Common::SceneInfo sceneInfo = m_simulationBuffer.getSceneInfo(initialTimestep);
		m_renderingBuffer.updateBuffer(std::move(sceneInfo));
		renderingThreadSemaphore->release();

		m_newestStateFrameTimestep = initialTimestep;
		mainLoop(initialTimestep);
	}

	void PhysicsThread::mainLoop(const Physics::Timestep& initialTimestep)
	{
		Physics::Timestep timestep = initialTimestep;
		while (!m_exitSignal.shouldStop())
		{
			timestep = timestep.next();
			m_notification.getNotification(timestep);
			sleepIfFuture(timestep);

			if (timestep > m_newestStateFrameTimestep)
			{
				Physics::PlayerInput ownInput = m_ownInput.getOwnInput();
				m_simulationBuffer.writeOwnInput(timestep, ownInput);

				m_simulationBuffer.update(timestep);

				Common::SceneInfo sceneInfo = m_simulationBuffer.getSceneInfo(timestep);
				m_renderingBuffer.updateBuffer(std::move(sceneInfo));

				if (m_gameMode == GameMode::multiplayer)
				{
					m_udpCommunication->sendControlFrame(timestep, m_ownId, ownInput);
				}

				m_newestStateFrameTimestep = timestep;
			}
			else
			{
				m_simulationBuffer.update(timestep);
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
