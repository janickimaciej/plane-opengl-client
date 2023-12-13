#pragma once

#include <cstdint>

namespace App
{
	enum class UDPFrameType
	{
		initReq,
		initRes,
		control,
		state
	};

	uint8_t toUInt8(UDPFrameType udpFrameType);
};
