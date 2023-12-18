#pragma once

#include "app/udp/udp_frame_type.hpp"
#include "common/airplane_type_name.hpp"
#include "physics/player_info.hpp"
#include "physics/player_input.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <asio/asio.hpp>

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace App
{
	class UDPCommunication
	{
	public:
		UDPCommunication(const std::string& serverIPAddress, int serverPort, int networkThreadPort,
			int physicsThreadPort);

		void sendInitReqFrame(Common::AirplaneTypeName airplaneTypeName);
		void sendControlFrame(const Physics::Timestep& timestep, int playerId,
			const Physics::PlayerInput& playerInput);

		bool receiveInitResFrame(Physics::Timestamp& sendTimestamp,
			Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp,
			int& playerId);
		bool receiveStateFrameWithOwnInfo(Physics::Timestep& timestep,
			std::unordered_map<int, Physics::PlayerInfo>& playerInfos, int ownId);
		bool receiveControlOrStateFrameWithOwnInfo(Physics::Timestamp& sendTimestamp,
			Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp,
			UDPFrameType& udpFrameType, Physics::Timestep& timestep, int& playerId,
			Physics::PlayerInput& playerInput,
			std::unordered_map<int, Physics::PlayerInfo>& playerInfos, int ownId);

	private:
		asio::io_context m_networkThreadIOContext{};
		asio::ip::udp::endpoint m_server{};
		asio::ip::udp::socket m_networkThreadSocket;
		
		asio::io_context m_physicsThreadIOContext{};
		asio::ip::udp::socket m_physicsThreadSocket;

		bool receiveFrameWithTimeout(
			std::function<bool(std::vector<std::uint8_t>, std::size_t)> frameHandler,
			const std::chrono::seconds& timeout);
		void setReceiveSocketTimeout(const std::chrono::duration<float>& timeout);
		static void completionHandler(std::shared_ptr<std::vector<std::uint8_t>>);
	};
};
