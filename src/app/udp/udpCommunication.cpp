#include "app/udp/udpCommunication.hpp"

#include "app/udp/udpFrameType.hpp"
#include "app/udp/udpSerializer.hpp"
#include "common/airplaneTypeName.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
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
	UDPCommunication::UDPCommunication(const std::string& serverIPAddress,
		int serverNetworkThreadPort, int serverPhysicsThreadPort, int clientNetworkThreadPort,
		int clientPhysicsThreadPort) :
		m_serverNetworkThread{asio::ip::address::from_string(serverIPAddress),
			static_cast<asio::ip::port_type>(serverNetworkThreadPort)},
		m_serverPhysicsThread{asio::ip::address::from_string(serverIPAddress),
			static_cast<asio::ip::port_type>(serverPhysicsThreadPort)},
		m_networkThreadSocket{m_networkThreadIOContext, asio::ip::udp::endpoint{asio::ip::udp::v4(),
			static_cast<asio::ip::port_type>(clientNetworkThreadPort)}},
		m_physicsThreadSocket{m_physicsThreadIOContext, asio::ip::udp::endpoint{asio::ip::udp::v4(),
			static_cast<asio::ip::port_type>(clientPhysicsThreadPort)}}
	{ }

	void UDPCommunication::sendInitReqFrame(Common::AirplaneTypeName airplaneTypeName)
	{
		std::vector<std::uint8_t> buffer{};
		UDPSerializer::serializeInitReqFrame(Physics::Timestamp::systemNow(), airplaneTypeName,
			buffer);

		m_networkThreadSocket.send_to(asio::buffer(buffer), m_serverNetworkThread);
	}

	void UDPCommunication::sendControlFrame(const Physics::Timestep& timestep, int playerId,
		const Physics::PlayerInput& playerInput)
	{
		std::shared_ptr<std::vector<std::uint8_t>> buffer =
			std::make_shared<std::vector<std::uint8_t>>();
		UDPSerializer::serializeControlFrame(Physics::Timestamp::systemNow(), Physics::Timestamp{},
			timestep, playerId, playerInput, *buffer);

		m_physicsThreadIOContext.run();
		m_physicsThreadIOContext.reset();
		m_physicsThreadSocket.async_send_to(asio::buffer(*buffer), m_serverNetworkThread,
			std::bind(completionHandler, buffer));
	}
	
	void UDPCommunication::sendKeepaliveFrames()
	{
		std::vector<std::uint8_t> buffer{};

		m_networkThreadSocket.send_to(asio::buffer(buffer), m_serverNetworkThread);
		m_networkThreadSocket.send_to(asio::buffer(buffer), m_serverPhysicsThread);
	}

	bool UDPCommunication::receiveInitResFrame(Physics::Timestamp& sendTimestamp,
		Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp, int& playerId)
	{
		static constexpr std::chrono::seconds timeout(10);
		return receiveFrameWithTimeout
		(
			[&sendTimestamp, &receiveTimestamp, &serverTimestamp, &playerId]
			(std::vector<std::uint8_t> buffer, std::size_t receivedSize)
			{
				if (buffer[0] == toUInt8(UDPFrameType::initRes))
				{
					receiveTimestamp = Physics::Timestamp::systemNow();
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeInitResFrame(receivedBuffer, sendTimestamp,
						serverTimestamp, playerId);
					return true;
				}
				return false;
			},
			timeout
		);
	}

	bool UDPCommunication::receiveStateFrameWithOwnInfo(Physics::Timestep& timestep,
		std::unordered_map<int, Physics::PlayerInfo>& playerInfos, int ownId)
	{
		static constexpr std::chrono::seconds timeout(10);
		return receiveFrameWithTimeout
		(
			[&timestep, &playerInfos, ownId]
			(std::vector<std::uint8_t> buffer, std::size_t receivedSize)
			{
				if (buffer[0] == toUInt8(UDPFrameType::state))
				{
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeStateFrame(receivedBuffer, timestep, playerInfos);
					if (playerInfos.contains(ownId))
					{
						return true;
					}
				}
				return false;
			},
			timeout
		);
	}

	bool UDPCommunication::receiveControlOrStateFrameWithOwnInfo(Physics::Timestamp& sendTimestamp,
		Physics::Timestamp& receiveTimestamp, Physics::Timestamp& serverTimestamp,
		UDPFrameType& udpFrameType, Physics::Timestep& timestep, int& playerId,
		Physics::PlayerInput& playerInput,
		std::unordered_map<int, Physics::PlayerInfo>& playerInfos, int ownId)
	{
		static constexpr std::chrono::seconds timeout(10);
		return receiveFrameWithTimeout
		(
			[&sendTimestamp, &receiveTimestamp, &serverTimestamp, &udpFrameType, &timestep,
			&playerId, &playerInput, &playerInfos, ownId]
			(std::vector<std::uint8_t> buffer, std::size_t receivedSize)
			{
				if (buffer[0] == toUInt8(UDPFrameType::control))
				{
					receiveTimestamp = Physics::Timestamp::systemNow();
					udpFrameType = UDPFrameType::control;
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeControlFrame(receivedBuffer, sendTimestamp,
						serverTimestamp, timestep, playerId, playerInput);
					return true;
				}
				else if (buffer[0] == toUInt8(UDPFrameType::state))
				{
					udpFrameType = UDPFrameType::state;
					std::vector<std::uint8_t> receivedBuffer(buffer.begin(),
						buffer.begin() + static_cast<int>(receivedSize));
					UDPSerializer::deserializeStateFrame(receivedBuffer, timestep, playerInfos);
					if (playerInfos.contains(ownId))
					{
						return true;
					}
				}
				return false;
			},
			timeout
		);
	}

	bool UDPCommunication::receiveFrameWithTimeout(
		std::function<bool(std::vector<std::uint8_t>, std::size_t)> frameHandler,
		const std::chrono::seconds& timeout)
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point expiration = now + timeout;
		
		static std::vector<std::uint8_t> buffer(maxFrameSize);
		while (now < expiration)
		{
			std::chrono::duration<float> remainder = expiration - now;
			setReceiveSocketTimeout(remainder);

			asio::ip::udp::endpoint server{};
			try
			{
				std::size_t receivedSize =
					m_networkThreadSocket.receive_from(asio::buffer(buffer), server);
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

	void UDPCommunication::setReceiveSocketTimeout(const std::chrono::duration<float>& timeout)
	{
		m_networkThreadSocket.set_option(
			asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO>
			{
				static_cast<int>
				(
					std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count()
				)
			});
	}

	void UDPCommunication::completionHandler(std::shared_ptr<std::vector<std::uint8_t>>)
	{ }
};
