#pragma once

#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/udp/udp_communication.hpp"
#include "common/airplane_type_name.hpp"
#include "common/map_name.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/notification.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"
#include "physics/spawner.hpp"

#include <memory>
#include <semaphore>
#include <string>
#include <thread>

namespace App
{
	class NetworkThread
	{
	public:
		NetworkThread(ExitSignal& exitSignal, GameMode gameMode,
			Common::AirplaneTypeName airplaneTypeName, Common::MapName mapName,
			const std::string& serverIPAddress, int serverNetworkThreadPort,
			int serverPhysicsThreadPort, int clientNetworkThreadPort, int clientPhysicsThreadPort,
			OwnInput& ownInput, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer,
			const std::shared_ptr<std::binary_semaphore>& renderingThreadSemaphore);
		void join();

	private:
		std::thread m_thread{};
		ExitSignal& m_exitSignal;

		Physics::SimulationClock m_simulationClock{};
		std::unique_ptr<Physics::SimulationBuffer> m_simulationBuffer{};
		int m_ownId{};
		Physics::Spawner m_spawner;

		Physics::Notification m_notification{m_simulationClock};
		Physics::Timestep m_frameCutoff{};
		std::unique_ptr<UDPCommunication> m_udpCommunication;

		void start(GameMode gameMode, Common::AirplaneTypeName airplaneTypeName,
			Common::MapName mapName, OwnInput& ownInput,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer,
			std::shared_ptr<std::binary_semaphore> renderingThreadSemaphore);
		bool startMultiplayer(Common::AirplaneTypeName airplaneTypeName, Common::MapName mapName,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void startSingleplayer(Common::AirplaneTypeName airplaneTypeName, Common::MapName mapName,
			std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer);
		void mainLoopMultiplayer();

		void handleControlFrame(const Physics::Timestamp& sendTimestamp,
			const Physics::Timestamp& receiveTimestamp, const Physics::Timestamp& serverTimestamp,
			const Physics::Timestep& timestep, int playerId,
			const Physics::PlayerInput& playerInput);
		void handleStateFrame(const Physics::Timestep& timestep,
			const std::unordered_map<int, Physics::PlayerInfo>& playerInfos);
	};
};
