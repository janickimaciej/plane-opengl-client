#include "app/udp/udp_connection.hpp"

#include "app/udp/udp_frame_type.hpp"
#include "app/udp/udp_serializer.hpp"
#include "common/airplane_type_name.hpp"
#include "common/user_info.hpp"
#include "common/user_input.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <asio/asio.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace App
{
	constexpr int clientPort = 34743;

	UDPConnection::UDPConnection(const std::string& ipAddress, int port) :
		m_server{asio::ip::address::from_string(ipAddress), static_cast<asio::ip::port_type>(port)},
		m_sendSocket{m_sendIOContext},
		m_receiveSocket{m_receiveIOContext, asio::ip::udp::endpoint{asio::ip::udp::v4(),
			clientPort}}
	{
		m_sendSocket.open(asio::ip::udp::v4());
	}

	void UDPConnection::sendInitReqFrame(Common::AirplaneTypeName airplaneTypeName)
	{
		std::vector<std::uint8_t> buffer{};
		UDPSerializer::serializeInitReqFrame(Physics::Timestamp::systemNow(), airplaneTypeName,
			buffer);

		m_sendSocket.send_to(asio::buffer(buffer), m_server);
	}

	void UDPConnection::sendControlFrame(const Physics::Timestep& timestep, int userId,
		const Common::UserInput& userInput)
	{
		std::shared_ptr<std::vector<std::uint8_t>> buffer =
			std::make_shared<std::vector<std::uint8_t>>();
		UDPSerializer::serializeControlFrame(Physics::Timestamp::systemNow(), Physics::Timestamp{},
			timestep, userId, userInput, *buffer);

		m_sendIOContext.run();
		m_sendIOContext.reset();
		m_sendSocket.async_send_to(asio::buffer(*buffer), m_server,
			std::bind(completionHandler, buffer));
	}

	bool UDPConnection::receiveInitResFrame(Physics::Timestamp& sendTimestamp,
		Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp, int& userId)
	{
		static constexpr std::chrono::seconds timeout(10);
		return receiveFrameWithTimeout
		(
			[&sendTimestamp, &receiveTimestamp, &serverTimestamp, &userId]
			(std::vector<std::uint8_t> buffer, std::size_t receivedSize)
			{
				if (buffer[0] == toUInt8(UDPFrameType::initRes))
				{
					receiveTimestamp = Physics::Timestamp::systemNow();
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeInitResFrame(receivedBuffer, sendTimestamp,
						serverTimestamp, userId);
					return true;
				}
				return false;
			},
			timeout
		);
	}

	bool UDPConnection::receiveStateFrameWithOwnInfo(Physics::Timestep& timestep,
		std::unordered_map<int, Common::UserInfo>& userInfos, int ownId)
	{
		static constexpr std::chrono::seconds timeout(10);
		return receiveFrameWithTimeout
		(
			[&timestep, &userInfos, ownId]
			(std::vector<std::uint8_t> buffer, std::size_t receivedSize)
			{
				if (buffer[0] == toUInt8(UDPFrameType::state))
				{
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeStateFrame(receivedBuffer, timestep, userInfos);
					if (userInfos.contains(ownId))
					{
						return true;
					}
				}
				return false;
			},
			timeout
		);
	}

	bool UDPConnection::receiveControlOrStateFrameWithOwnInfo(Physics::Timestamp& sendTimestamp,
		Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp,
		UDPFrameType& udpFrameType, Physics::Timestep& timestep, int& userId,
		Common::UserInput& userInput, std::unordered_map<int, Common::UserInfo>& userInfos,
		int ownId)
	{
		static constexpr std::chrono::seconds timeout(10);
		return receiveFrameWithTimeout
		(
			[&sendTimestamp, &receiveTimestamp, &serverTimestamp, &udpFrameType, &timestep, &userId,
			&userInput, &userInfos, ownId]
			(std::vector<std::uint8_t> buffer, std::size_t receivedSize)
			{
				if (buffer[0] == toUInt8(UDPFrameType::control))
				{
					udpFrameType = UDPFrameType::control;
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeControlFrame(receivedBuffer, sendTimestamp,
						serverTimestamp, timestep, userId, userInput);
				}
				else if (buffer[0] == toUInt8(UDPFrameType::state))
				{
					receiveTimestamp = Physics::Timestamp::systemNow();
					udpFrameType = UDPFrameType::state;
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeStateFrame(receivedBuffer, timestep, userInfos);
					if (userInfos.contains(ownId))
					{
						return true;
					}
				}
				return false;
			},
			timeout
		);
	}

	bool UDPConnection::receiveFrameWithTimeout(
		std::function<bool(std::vector<std::uint8_t>, std::size_t)> frameHandler,
		const std::chrono::seconds& timeout)
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point expiration = now + timeout;
		
		static std::vector<std::uint8_t> buffer(maxFrameSize);
		while(now < expiration)
		{
			std::chrono::duration<float> remainder = expiration - now;
			setReceiveSocketTimeout(remainder);

			asio::ip::udp::endpoint server{};
			try
			{
				std::size_t receivedSize =
					m_receiveSocket.receive_from(asio::buffer(buffer), server);
				if (frameHandler(buffer, receivedSize))
				{
					return true;
				}
			}
			catch (std::exception&)
			{ }

			now = std::chrono::steady_clock::now();
		}
		return false;
	}

	void UDPConnection::setReceiveSocketTimeout(const std::chrono::duration<float>& timeout)
	{
		m_receiveSocket.set_option(asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO>
			{
				static_cast<int>
				(
					std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count()
				)
			});
	}

	void UDPConnection::completionHandler(std::shared_ptr<std::vector<std::uint8_t>>)
	{ }
};
