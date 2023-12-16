#pragma once

#include "app/udp/udp_frame_type.hpp"

#include <bitsery/traits/array.h>

#include <array>

namespace App
{
	struct InitResFrame
	{
		unsigned char frameType = toUInt8(UDPFrameType::initRes);
		std::array<unsigned char, 2> clientTimestamp{};
		std::array<unsigned char, 2> serverTimestamp{};
		unsigned char playerId{};
	};

	template <typename T>
	void serialize(T& t, InitResFrame& frame)
	{
		t.value1b(frame.frameType);
		t.container1b(frame.clientTimestamp);
		t.container1b(frame.serverTimestamp);
		t.value1b(frame.playerId);
	}
};
