#include "app/udp/udp_serializer.hpp"

#include "app/udp/frame/control_frame.hpp"
#include "app/udp/frame/init_req_frame.hpp"
#include "app/udp/frame/init_res_frame.hpp"
#include "app/udp/frame/state_frame.hpp"
#include "app/udp/udp_frame_type.hpp"
#include "common/airplane_type_name.hpp"
#include "physics/player_info.hpp"
#include "physics/player_input.hpp"
#include "physics/player_state.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace App
{
	using OutputAdapter = bitsery::OutputBufferAdapter<std::vector<std::uint8_t>>;
	using InputAdapter = bitsery::InputBufferAdapter<std::vector<std::uint8_t>>;

	void UDPSerializer::serializeInitReqFrame(const Physics::Timestamp& clientTimestamp,
		Common::AirplaneTypeName airplaneTypeName, std::vector<std::uint8_t>& buffer)
	{
		InitReqFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.airplaneType = toUChar(airplaneTypeName);

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::serializeControlFrame(const Physics::Timestamp& clientTimestamp,
		const Physics::Timestamp& serverTimestamp, const Physics::Timestep& timestep, int playerId,
		const Physics::PlayerInput& playerInput, std::vector<std::uint8_t>& buffer)
	{
		ControlFrame frame{};
		frame.clientTimestamp = packTimestamp(clientTimestamp);
		frame.serverTimestamp = packTimestamp(serverTimestamp);
		frame.timestep = packTimestep(timestep);
		frame.playerId = static_cast<unsigned char>(playerId);
		frame.pitch = static_cast<signed char>(playerInput.pitch * 100 + 0.5f);
		frame.yaw = static_cast<signed char>(playerInput.yaw * 100 + 0.5f);
		frame.roll = static_cast<signed char>(playerInput.roll * 100 + 0.5f);
		frame.thrust = static_cast<unsigned char>(playerInput.thrust * 100 + 0.5f);
		frame.trigger = playerInput.trigger;

		std::size_t size = bitsery::quickSerialization<OutputAdapter>(buffer, frame);
		buffer.resize(size);
	}

	void UDPSerializer::deserializeInitResFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp, int& playerId)
	{
		InitResFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		serverTimestamp = unpackTimestamp(frame.serverTimestamp);
		playerId = frame.playerId;
	}

	void UDPSerializer::deserializeControlFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
		Physics::Timestep& timestep, int& playerId, Physics::PlayerInput& playerInput)
	{
		ControlFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		clientTimestamp = unpackTimestamp(frame.clientTimestamp);
		serverTimestamp = unpackTimestamp(frame.serverTimestamp);
		timestep = unpackTimestep(frame.timestep);
		playerId = frame.playerId;
		playerInput.pitch = static_cast<float>(frame.pitch) / 100;
		playerInput.yaw = static_cast<float>(frame.yaw) / 100;
		playerInput.roll = static_cast<float>(frame.roll) / 100;
		playerInput.thrust = static_cast<float>(frame.thrust) / 100;
		playerInput.trigger = static_cast<float>(frame.trigger) / 100;
	}

	void UDPSerializer::deserializeStateFrame(const std::vector<std::uint8_t>& buffer,
		Physics::Timestep& timestep, std::unordered_map<int, Physics::PlayerInfo>& playerInfos)
	{
		StateFrame frame{};
		bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.size()}, frame);

		timestep = unpackTimestep(frame.timestep);
		for (const StateFramePlayerInfo& playerInfo : frame.playerInfos)
		{
			playerInfos.insert({playerInfo.playerId,
				Physics::PlayerInfo
				{
					Physics::PlayerInput
					{
						static_cast<float>(playerInfo.pitch) / 100,
						static_cast<float>(playerInfo.yaw) / 100,
						static_cast<float>(playerInfo.roll) / 100,
						static_cast<float>(playerInfo.thrust) / 100,
						playerInfo.trigger
					},
					Physics::PlayerState
					{
						playerInfo.hp,
						Common::State(playerInfo.state),
						static_cast<Common::AirplaneTypeName>(playerInfo.airplaneType)
					}
				}});
		}
	}
	
	std::array<unsigned char, 2> UDPSerializer::packTimestamp(const Physics::Timestamp& timestamp)
	{
		std::array<unsigned char, 2> serializedTimestamp{};
		serializedTimestamp[0] = static_cast<unsigned char>(timestamp.second);
		serializedTimestamp[0] <<= 2;
		serializedTimestamp[0] |= static_cast<unsigned char>(timestamp.millisecond >> 8);
		serializedTimestamp[1] = static_cast<unsigned char>(timestamp.millisecond);
		return serializedTimestamp;
	}

	std::array<unsigned char, 2> UDPSerializer::packTimestep(const Physics::Timestep& timestep)
	{
		std::array<unsigned char, 2> serializedTimestep{};
		serializedTimestep[0] = static_cast<unsigned char>(timestep.second);
		serializedTimestep[0] <<= 2;
		serializedTimestep[0] |= static_cast<unsigned char>(timestep.frame >> 8);
		serializedTimestep[1] = static_cast<unsigned char>(timestep.frame);
		return serializedTimestep;
	}

	Physics::Timestamp UDPSerializer::unpackTimestamp(const std::array<unsigned char, 2>& timestamp)
	{
		Physics::Timestamp deserializedTimestamp{};
		deserializedTimestamp.second = static_cast<unsigned int>(timestamp[0] >> 2);
		deserializedTimestamp.millisecond =
			static_cast<unsigned int>(timestamp[0] - ((timestamp[0] >> 2) << 2));
		deserializedTimestamp.millisecond <<= 8;
		deserializedTimestamp.millisecond |= static_cast<unsigned int>(timestamp[1]);
		return deserializedTimestamp;
	}

	Physics::Timestep UDPSerializer::unpackTimestep(const std::array<unsigned char, 2>& timestep)
	{
		Physics::Timestep deserializedTimestep{};
		deserializedTimestep.second = static_cast<unsigned int>(timestep[0] >> 2);
		deserializedTimestep.frame =
			static_cast<unsigned int>(timestep[0] - ((timestep[0] >> 2) << 2));
		deserializedTimestep.frame <<= 8;
		deserializedTimestep.frame |= static_cast<unsigned int>(timestep[1]);
		return deserializedTimestep;
	}
};
