#pragma once

#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/udp_server.hpp"
#include "common/airplane_type_name.hpp"
#include "common/sync/notification.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <string>
#include <thread>

namespace App
{
	class NetworkThread
	{
	public:
		NetworkThread(std::binary_semaphore& renderingSemaphore, GameMode gameMode,
			const std::string& ipAddress, int port, OwnInput& ownInput,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void stop();
		void join();

	private:
		std::thread m_thread;
		std::atomic<bool> m_shouldStop = false;
		std::binary_semaphore m_mainLoopSingleplayer{0};

		std::unique_ptr<Physics::SimulationClock> m_simulationClock{};
		std::unique_ptr<Physics::SimulationBuffer> m_simulationBuffer{};
		Common::Notification m_notification{};

		UDPServer m_udpServer;

		void start(std::binary_semaphore& renderingSemaphore, GameMode gameMode,
			OwnInput& ownInput, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void startMultiplayer(std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void startSingleplayer(std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void mainLoopMultiplayer();
	};
};
