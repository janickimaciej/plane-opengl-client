#pragma once

#include "app/udp/frame/state_frame_player_info.hpp"
#include "app/udp/udp_frame_type.hpp"

#include <bitsery/traits/array.h>
#include <bitsery/traits/vector.h>

#include <cstddef>
#include <vector>

namespace App
{
	inline constexpr std::size_t maxPlayerCount = 32;
	inline constexpr std::size_t vectorSerializedSize = 4; // with margin
	inline constexpr std::size_t emptyStateFrameSerializedSize = 3 + vectorSerializedSize;

	struct StateFrame
	{
		unsigned char frameType = toUInt8(UDPFrameType::state);
		std::array<unsigned char, 2> timestep{};
		std::vector<StateFramePlayerInfo> playerInfos{};
	};

	template <typename T>
	void serialize(T& t, StateFrame& frame)
	{
		t.value1b(frame.frameType);
		t.container1b(frame.timestep);
		t.container(frame.playerInfos, maxPlayerCount);
	}
};
