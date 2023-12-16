#pragma once

#include "app/udp/frame/state_frame.hpp"
#include "common/airplane_type_name.hpp"
#include "physics/player_info.hpp"
#include "physics/player_input.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace App
{
	inline constexpr std::size_t maxFrameSize = emptyStateFrameSerializedSize + maxPlayerCount *
		stateFramePlayerInfoSerializedSize;

	class UDPSerializer
	{
	public:
		static void serializeInitReqFrame(const Physics::Timestamp& clientTimestamp,
			Common::AirplaneTypeName airplaneTypeName, std::vector<std::uint8_t>& buffer);
		static void serializeControlFrame(const Physics::Timestamp& clientTimestamp,
			const Physics::Timestamp& serverTimestamp, const Physics::Timestep& timestep,
			int playerId, const Physics::PlayerInput& playerInput,
			std::vector<std::uint8_t>& buffer);

		static void deserializeInitResFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
			int& playerId);
		static void deserializeControlFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
			Physics::Timestep& timestep, int& playerId, Physics::PlayerInput& playerInput);
		static void deserializeStateFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestep& timestep, std::unordered_map<int, Physics::PlayerInfo>& playerInfos);

	private:
		static std::array<unsigned char, 2> packTimestamp(const Physics::Timestamp& timestamp);
		static std::array<unsigned char, 2> packTimestep(const Physics::Timestep& timestep);

		static Physics::Timestamp unpackTimestamp(const std::array<unsigned char, 2>& timestamp);
		static Physics::Timestep unpackTimestep(const std::array<unsigned char, 2>& timestep);
	};
};
