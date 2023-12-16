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
	class UDPConnection
	{
	public:
		UDPConnection(const std::string& ipAddress, int port);

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
		asio::io_context m_sendIOContext{};
		asio::ip::udp::endpoint m_server{};
		asio::ip::udp::socket m_sendSocket;
		
		asio::io_context m_receiveIOContext{};
		asio::ip::udp::socket m_receiveSocket;

		bool receiveFrameWithTimeout(
			std::function<bool(std::vector<std::uint8_t>, std::size_t)> frameHandler,
			const std::chrono::seconds& timeout);
		void setReceiveSocketTimeout(const std::chrono::duration<float>& timeout);
		static void completionHandler(std::shared_ptr<std::vector<std::uint8_t>>);
	};
};
