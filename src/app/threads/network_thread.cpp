#include "app/threads/network_thread.hpp"

#include "app/exit_code.hpp"
#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/threads/physics_thread.hpp"
#include "app/udp/udp_communication.hpp"
#include "app/udp/udp_frame_type.hpp"
#include "common/airplane_type_name.hpp"
#include "common/config.hpp"
#include "common/map_name.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/airplane_definitions.hpp"
#include "physics/notification.hpp"
#include "physics/player_info.hpp"
#include "physics/player_input.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"
#include "physics/timestamp.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <string>
#include <thread>
#include <unordered_map>

namespace App
{
	NetworkThread::NetworkThread(ExitSignal& exitSignal, GameMode gameMode,
		Common::AirplaneTypeName airplaneTypeName, Common::MapName mapName,
		const std::string& serverIPAddress, int serverNetworkThreadPort,
		int serverPhysicsThreadPort, int clientNetworkThreadPort, int clientPhysicsThreadPort,
		OwnInput& ownInput, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer,
		const std::shared_ptr<std::binary_semaphore>& renderingThreadSemaphore) :
		m_exitSignal{exitSignal}
	{
		if (gameMode == GameMode::multiplayer)
		{
			m_udpCommunication = std::make_unique<UDPCommunication>(serverIPAddress,
				serverNetworkThreadPort, serverPhysicsThreadPort, clientNetworkThreadPort,
				clientPhysicsThreadPort);
		}
		m_thread = std::thread(
			[this, gameMode, airplaneTypeName, mapName, &ownInput, &renderingBuffer,
				renderingThreadSemaphore]
			{
				this->start(gameMode, airplaneTypeName, mapName, ownInput, renderingBuffer,
					std::move(renderingThreadSemaphore));
			});
	}

	void NetworkThread::join()
	{
		m_thread.join();
	}

	void NetworkThread::start(GameMode gameMode, Common::AirplaneTypeName airplaneTypeName,
		Common::MapName mapName, OwnInput& ownInput,
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer,
		std::shared_ptr<std::binary_semaphore> renderingThreadSemaphore)
	{
		if (gameMode == GameMode::multiplayer)
		{
			if (!startMultiplayer(airplaneTypeName, mapName, renderingBuffer))
			{
				m_exitSignal.exit(ExitCode::failedToConnect);
				return;
			}
		}
		else
		{
			startSingleplayer(airplaneTypeName, mapName, renderingBuffer);
		}
		PhysicsThread physicsThread{m_exitSignal, gameMode, m_simulationClock, *m_simulationBuffer,
			m_ownId, m_notification, *renderingBuffer, ownInput, m_udpCommunication.get(),
			renderingThreadSemaphore};
		if (gameMode == GameMode::multiplayer)
		{
			mainLoopMultiplayer();
		}
		else
		{
			std::shared_ptr<std::binary_semaphore> semaphore =
				std::make_shared<std::binary_semaphore>(0);
			m_exitSignal.registerOnExit([semaphore] ()
				{
					semaphore->release();
				});
			semaphore->acquire();
		}
		physicsThread.join();
	}

	bool NetworkThread::startMultiplayer(Common::AirplaneTypeName airplaneTypeName,
		Common::MapName mapName, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		static constexpr int initReqFrameCount = 10;
		for (int i = 0; i < initReqFrameCount; ++i)
		{
			m_udpCommunication->sendInitReqFrame(airplaneTypeName);
		}

		Physics::Timestamp sendTimestamp{};
		Physics::Timestamp receiveTimestamp{};
		Physics::Timestamp serverTimestamp{};
		if (!m_udpCommunication->receiveInitResFrame(sendTimestamp, receiveTimestamp,
			serverTimestamp, m_ownId))
		{
			m_exitSignal.exit(ExitCode::failedToConnect);
			return false;
		}

		m_udpCommunication->sendKeepaliveFrames();

		m_simulationClock.initializeOffset(sendTimestamp, receiveTimestamp, serverTimestamp);

		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(m_ownId, mapName);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(m_ownId);

		Physics::Timestep initialTimestep{};
		std::unordered_map<int, Physics::PlayerInfo> playerInfos{};
		if (!m_udpCommunication->receiveStateFrameWithOwnInfo(initialTimestep, playerInfos,
			m_ownId))
		{
			m_exitSignal.exit(ExitCode::failedToConnect);
			return false;
		}
		m_simulationBuffer->writeStateFrame(initialTimestep, playerInfos);
		m_frameCutoff = initialTimestep;

		m_notification.setNotification(initialTimestep, true);

		return true;
	}

	void NetworkThread::startSingleplayer(Common::AirplaneTypeName airplaneTypeName,
		Common::MapName mapName, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		constexpr int ownId = 0;
		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(ownId, mapName);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(ownId);

		Physics::Timestep initialTimestep = m_simulationClock.getTime();
		
		Physics::PlayerInfo ownInfo;

		ownInfo.state.hp = Physics::airplaneDefinitions[toSizeT(airplaneTypeName)].initialHP;
		constexpr glm::vec3 initialPosition{10000, 500, 20000};
		ownInfo.state.state.position = initialPosition;
		ownInfo.state.state.velocity =
			Physics::airplaneDefinitions[toSizeT(airplaneTypeName)].initialVelocity;
		ownInfo.state.airplaneTypeName = airplaneTypeName;

		std::unordered_map<int, Physics::PlayerInfo> playerInfos;
		playerInfos.insert({ownId, ownInfo});
		m_simulationBuffer->writeStateFrame(initialTimestep, std::move(playerInfos));

		m_notification.setNotification(initialTimestep, true);
	}

	void NetworkThread::mainLoopMultiplayer()
	{
		while (!m_exitSignal.shouldStop())
		{
			Physics::Timestamp sendTimestamp{};
			Physics::Timestamp receiveTimestamp{};
			Physics::Timestamp serverTimestamp{};
			UDPFrameType udpFrameType{};
			Physics::Timestep timestep{};
			int playerId{};
			Physics::PlayerInput playerInput{};
			std::unordered_map<int, Physics::PlayerInfo> playerInfos{};

			if (!m_udpCommunication->receiveControlOrStateFrameWithOwnInfo(sendTimestamp,
				receiveTimestamp, serverTimestamp, udpFrameType, timestep, playerId, playerInput,
				playerInfos, m_ownId))
			{
				m_exitSignal.exit(ExitCode::connectionLost);
				return;
			}
			
			constexpr Physics::Timestep frameAgeCutoffOffset{0,
				static_cast<unsigned int>(Common::stepsPerSecond * 0.9f)};
			Physics::Timestep frameAgeCutoff = m_simulationClock.getTime() - frameAgeCutoffOffset;
			if (m_frameCutoff < frameAgeCutoff)
			{
				m_frameCutoff = frameAgeCutoff;
			}

			if (timestep <= m_frameCutoff)
			{
				continue;
			}

			if (udpFrameType == UDPFrameType::control)
			{
				handleControlFrame(sendTimestamp, receiveTimestamp, serverTimestamp, timestep,
					playerId, playerInput);
			}
			else if (udpFrameType == UDPFrameType::state)
			{
				m_udpCommunication->sendKeepaliveFrames();
				handleStateFrame(timestep, playerInfos);
			}
		}
	}

	void NetworkThread::handleControlFrame(const Physics::Timestamp& sendTimestamp,
		const Physics::Timestamp& receiveTimestamp, const Physics::Timestamp& serverTimestamp,
		const Physics::Timestep& timestep, int playerId, const Physics::PlayerInput& playerInput)
	{
		if (playerId == m_ownId)
		{
			m_simulationClock.updateOffset(sendTimestamp, receiveTimestamp,
				serverTimestamp);
		}
		else
		{
			m_simulationBuffer->writeControlFrame(timestep, playerId, playerInput);
			m_notification.setNotification(timestep, false);
		}
	}

	void NetworkThread::handleStateFrame(const Physics::Timestep& timestep,
		const std::unordered_map<int, Physics::PlayerInfo>& playerInfos)
	{
		m_frameCutoff = timestep;

		m_simulationBuffer->writeStateFrame(timestep, playerInfos);
		m_notification.setNotification(timestep, true);
	}
};
