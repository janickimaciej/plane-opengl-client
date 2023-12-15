#include "app/threads/network_thread.hpp"

#include "app/exit_code.hpp"
#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/threads/physics_thread.hpp"
#include "app/udp/udp_connection.hpp"
#include "app/udp/udp_frame_type.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/rendering_buffer.hpp"
#include "physics/notification.hpp"
#include "physics/simulation_buffer.hpp"
#include "physics/simulation_clock.hpp"
#include "physics/timestamp.hpp"
#include "physics/user_info.hpp"
#include "physics/user_input.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <string>
#include <thread>
#include <unordered_map>

namespace App
{
	NetworkThread::NetworkThread(ExitSignal& exitSignal, std::binary_semaphore& renderingSemaphore,
		GameMode gameMode, Common::AirplaneTypeName airplaneTypeName, const std::string& ipAddress,
		int port, OwnInput& ownInput, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer) :
		m_exitSignal{exitSignal},
		m_thread
		{
			[this, &renderingSemaphore, gameMode, airplaneTypeName, &ownInput, &renderingBuffer]
			{
				this->start(renderingSemaphore, gameMode, airplaneTypeName, ownInput,
					renderingBuffer);
			}
		}
	{
		if (gameMode == GameMode::multiplayer)
		{
			m_udpConnection = std::make_unique<UDPConnection>(ipAddress, port);
		}
	}

	void NetworkThread::join()
	{
		m_thread.join();
	}

	void NetworkThread::start(std::binary_semaphore& renderingSemaphore, GameMode gameMode,
		Common::AirplaneTypeName airplaneTypeName, OwnInput& ownInput,
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		if (gameMode == GameMode::multiplayer)
		{
			if (!startMultiplayer(airplaneTypeName, renderingBuffer))
			{
				m_exitSignal.exit(ExitCode::failedToConnect);
				return;
			}
		}
		else
		{
			startSingleplayer(renderingBuffer);
		}
		PhysicsThread physicsThread{m_exitSignal, gameMode, renderingSemaphore, m_simulationClock,
			*m_simulationBuffer, m_ownId, m_notification, *renderingBuffer, ownInput,
			m_udpConnection.get()};
		if (gameMode == GameMode::multiplayer)
		{
			mainLoopMultiplayer();
		}
		else
		{
			m_exitSignal.acquireNetworkThreadSemaphore();
		}
		physicsThread.join();
	}

	bool NetworkThread::startMultiplayer(Common::AirplaneTypeName airplaneTypeName,
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		static constexpr int initFrameCount = 10;
		for (int i = 0; i < initFrameCount; ++i)
		{
			m_udpConnection->sendInitReqFrame(airplaneTypeName);
		}

		Physics::Timestamp sendTimestamp{};
		Physics::Timestamp receiveTimestamp{};
		Physics::Timestamp serverTimestamp{};
		if (!m_udpConnection->receiveInitResFrame(sendTimestamp, receiveTimestamp,
			serverTimestamp, m_ownId))
		{
			return false;
		}

		m_simulationClock.initializeOffset(sendTimestamp, receiveTimestamp, serverTimestamp);

		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(m_ownId);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(m_ownId);

		Physics::Timestep initialTimestep{};
		std::unordered_map<int, Physics::UserInfo> userInfos{};
		if (!m_udpConnection->receiveStateFrameWithOwnInfo(initialTimestep, userInfos, m_ownId))
		{
			return false;
		}
		m_simulationBuffer->writeStateFrame(initialTimestep, userInfos);
		m_frameCutoff = initialTimestep;

		m_notification.setNotification(initialTimestep, true);

		return true;
	}

	void NetworkThread::startSingleplayer(
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		constexpr int ownId = 0;
		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(ownId);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(ownId);

		Physics::Timestep initialTimestep = m_simulationClock.getTime();
		
		Physics::UserInfo ownInfo;
		constexpr int initialHP = 100;
		ownInfo.state.hp = initialHP;
		constexpr glm::vec3 initialPosition{0, 50, 100};
		ownInfo.state.state.position = initialPosition;
		constexpr glm::vec3 initialVelocity{0, 0, -100};
		ownInfo.state.state.velocity = initialVelocity;

		std::unordered_map<int, Physics::UserInfo> userInfos;
		userInfos.insert({ownId, ownInfo});
		m_simulationBuffer->writeStateFrame(initialTimestep, userInfos);

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
			int userId{};
			Physics::UserInput userInput{};
			std::unordered_map<int, Physics::UserInfo> userInfos{};

			if (!m_udpConnection->receiveControlOrStateFrameWithOwnInfo(sendTimestamp,
				receiveTimestamp, serverTimestamp, udpFrameType, timestep, userId, userInput,
				userInfos, m_ownId))
			{
				m_exitSignal.exit(ExitCode::connectionLost);
				return;
			}
			
			constexpr Physics::Timestep frameAgeCutoffOffset{0,
				static_cast<unsigned int>(Physics::framesPerSecond * 0.9f)};
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
				m_simulationClock.updateOffset(sendTimestamp, receiveTimestamp, serverTimestamp);
				m_simulationBuffer->writeControlFrame(timestep, userId, userInput);
				m_notification.setNotification(timestep, false);
			}
			else
			{
				m_frameCutoff = timestep;

				m_simulationBuffer->writeStateFrame(timestep, userInfos);
				m_notification.setNotification(timestep, true);
			}
		}
	}
};
