#pragma once

#include "app/udp/udp_frame_type.hpp"
#include "common/airplane_type_name.hpp"
#include "common/user_info.hpp"
#include "common/user_input.hpp"
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
		void sendControlFrame(const Physics::Timestep& timestep, int userId,
			const Common::UserInput& userInput);

		bool receiveInitResFrame(Physics::Timestamp& sendTimestamp,
			Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp, int& userId);
		bool receiveStateFrameWithOwnInfo(Physics::Timestep& timestep,
			std::unordered_map<int, Common::UserInfo>& userInfos, int ownId);
		bool receiveControlOrStateFrameWithOwnInfo(Physics::Timestamp& sendTimestamp,
			Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp,
			UDPFrameType& udpFrameType, Physics::Timestep& timestep, int& userId,
			Common::UserInput& userInput, std::unordered_map<int, Common::UserInfo>& userInfos,
			int ownId);

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
