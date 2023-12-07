#include "app/threads/physics_thread.hpp"

#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "common/frame.hpp"
#include "common/sync/airplane_info.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <thread>

namespace App
{
	PhysicsThread::PhysicsThread(GameMode gameMode, std::binary_semaphore& renderingSemaphore,
		const Physics::SimulationClock& simulationClock,
		Physics::SimulationBuffer& simulationBuffer, Common::Notification& notification,
		Graphics::RenderingBuffer& renderingBuffer, OwnInput& ownInput, UDPServer& udpServer) :
		m_gameMode{gameMode},
		m_simulationClock{simulationClock},
		m_simulationBuffer{simulationBuffer},
		m_notification{notification},
		m_renderingBuffer{renderingBuffer},
		m_ownInput{ownInput},
		m_udpServer{udpServer},
		m_thread
		{
			[this, &renderingSemaphore]
			{ 
				this->start(renderingSemaphore);
			}
		}
	{ }

	void PhysicsThread::stop()
	{
		m_shouldStop = true;
	}

	void PhysicsThread::join()
	{
		m_thread.join();
	}

	void PhysicsThread::start(std::binary_semaphore& renderingSemaphore)
	{
		int initialSecond{};
		unsigned int initialFrame{};

		m_notification.forceGetNotification(initialSecond, initialFrame);
		
		m_simulationBuffer.setOwnInput(initialSecond, initialFrame, Common::UserInput{});
		m_simulationBuffer.update(initialSecond, initialFrame);

		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos =
			m_simulationBuffer.getAirplaneInfos(initialFrame);
		m_renderingBuffer.updateBuffer(std::move(airplaneInfos));

		renderingSemaphore.release();
		mainLoop(initialSecond, initialFrame);
	}

	void PhysicsThread::mainLoop(int initialSecond, unsigned int initialFrame)
	{
		int second = initialSecond;
		unsigned int frame = initialFrame;
		while(!m_shouldStop)
		{
			Common::nextFrame(second, frame);
			m_notification.getNotification(second, frame);
			sleepIfFuture(second, frame);

			Common::UserInput ownInput = m_ownInput.getOwnInput();
			m_simulationBuffer.setOwnInput(second, frame, ownInput);
			m_simulationBuffer.update(second, frame);

			std::unordered_map<int, Common::AirplaneInfo> airplaneInfos =
				m_simulationBuffer.getAirplaneInfos(frame);
			m_renderingBuffer.updateBuffer(std::move(airplaneInfos));

			if (m_gameMode == GameMode::multiplayer)
			{
				sendControlFrame();
			}
		}
	}

	void PhysicsThread::sleepIfFuture(int second, unsigned int frame)
	{
		int currentSecond{};
		unsigned int currentFrame{};
		m_simulationClock.getTime(currentSecond, currentFrame);
		while (Common::earlierThan(currentSecond, currentFrame, second, frame))
		{
			//constexpr int sleepMilliseconds = 1000 / Common::framesPerSecond;
			//std::this_thread::sleep_for(std::chrono::milliseconds(sleepMilliseconds));
			m_simulationClock.getTime(currentSecond, currentFrame);
		}
	}

	void PhysicsThread::sendControlFrame()
	{
		// TODO
	}
};
