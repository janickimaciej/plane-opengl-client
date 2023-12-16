#pragma once

#include "app/udp/udp_frame_type.hpp"

#include <bitsery/traits/array.h>

#include <array>

namespace App
{
	struct ControlFrame
	{
		unsigned char frameType = toUInt8(UDPFrameType::control);
		std::array<unsigned char, 2> clientTimestamp{};
		std::array<unsigned char, 2> serverTimestamp{};
		std::array<unsigned char, 2> timestep{};
		unsigned char playerId{};
		signed char pitch{};
		signed char yaw{};
		signed char roll{};
		unsigned char thrust{};
		bool trigger{};
	};

	template <typename T>
	void serialize(T& t, ControlFrame& frame)
	{
		t.value1b(frame.frameType);
		t.container1b(frame.clientTimestamp);
		t.container1b(frame.serverTimestamp);
		t.container1b(frame.timestep);
		t.value1b(frame.playerId);
		t.value1b(frame.pitch);
		t.value1b(frame.yaw);
		t.value1b(frame.roll);
		t.value1b(frame.thrust);
		t.value1b(frame.trigger);
	}
};
