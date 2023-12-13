#pragma once

#include "app/udp/frame/state_frame.hpp"
#include "common/airplane_type_name.hpp"
#include "common/user_info.hpp"
#include "common/user_input.hpp"
#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace App
{
	inline constexpr std::size_t maxFrameSize = emptyStateFrameSerializedSize + maxUserCount *
		stateFrameUserInfoSerializedSize;

	class UDPSerializer
	{
	public:
		static void serializeInitReqFrame(const Physics::Timestamp& clientTimestamp,
			Common::AirplaneTypeName airplaneTypeName, std::vector<std::uint8_t>& buffer);
		static void serializeControlFrame(const Physics::Timestamp& clientTimestamp,
			const Physics::Timestamp& serverTimestamp, const Physics::Timestep& timestep,
			int userId, const Common::UserInput& userInput, std::vector<std::uint8_t>& buffer);

		static void deserializeInitResFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp, int& userId);
		static void deserializeControlFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestamp& clientTimestamp, Physics::Timestamp& serverTimestamp,
			Physics::Timestep& timestep, int& userId, Common::UserInput& userInput);
		static void deserializeStateFrame(const std::vector<std::uint8_t>& buffer,
			Physics::Timestep& timestep, std::unordered_map<int, Common::UserInfo>& userInfos);

	private:
		static std::array<unsigned char, 2> packTimestamp(const Physics::Timestamp& timestamp);
		static std::array<unsigned char, 2> packTimestep(const Physics::Timestep& timestep);

		static Physics::Timestamp unpackTimestamp(const std::array<unsigned char, 2>& timestamp);
		static Physics::Timestep unpackTimestep(const std::array<unsigned char, 2>& timestep);
	};
};
