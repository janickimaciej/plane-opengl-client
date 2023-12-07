#pragma once

#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/udp_server.hpp"
#include "common/sync/notification.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <thread>

namespace App
{
	class PhysicsThread
	{
	public:
		PhysicsThread(GameMode gameMode, std::binary_semaphore& renderingSemaphore,
			const Physics::SimulationClock& simulationClock,
			Physics::SimulationBuffer& simulationBuffer, Common::Notification& notification,
			Graphics::RenderingBuffer& renderingBuffer, OwnInput& ownInput, UDPServer& udpServer);
		void stop();
		void join();

	private:
		std::thread m_thread;
		std::atomic<bool> m_shouldStop = false;

		GameMode m_gameMode;

		const Physics::SimulationClock& m_simulationClock;
		Physics::SimulationBuffer& m_simulationBuffer;
		Common::Notification& m_notification;

		Graphics::RenderingBuffer& m_renderingBuffer;
		OwnInput& m_ownInput;

		UDPServer& m_udpServer;

		void start(std::binary_semaphore& renderingSemaphore);
		void mainLoop(int initialSecond, unsigned int initialFrame);
		void sleepIfFuture(int second, unsigned int frame);
		void sendControlFrame();
	};
};
