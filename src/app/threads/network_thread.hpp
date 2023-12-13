#pragma once

#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/udp/udp_connection.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/notification.hpp"
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
		NetworkThread(ExitSignal& exitSignal, std::binary_semaphore& renderingSemaphore,
			GameMode gameMode, Common::AirplaneTypeName airplaneTypeName,
			const std::string& ipAddress, int port, OwnInput& ownInput,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void join();

	private:
		std::thread m_thread;
		ExitSignal& m_exitSignal;

		Physics::SimulationClock m_simulationClock{};
		std::unique_ptr<Physics::SimulationBuffer> m_simulationBuffer{};
		int m_ownId{};

		Physics::Notification m_notification{};
		Physics::Timestep m_latestStateFrameTimestep{};
		std::unique_ptr<UDPConnection> m_udpConnection;

		void start(std::binary_semaphore& renderingSemaphore, GameMode gameMode,
			Common::AirplaneTypeName airplaneTypeName, OwnInput& ownInput,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		bool startMultiplayer(Common::AirplaneTypeName airplaneTypeName,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void startSingleplayer(std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void mainLoopMultiplayer();
	};
};
