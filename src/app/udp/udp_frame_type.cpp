#include "app/udp/udp_frame_type.hpp"

#include <cstdint>

namespace App
{
	uint8_t toUInt8(UDPFrameType udpFrameType)
	{
		return static_cast<uint8_t>(udpFrameType);
	}
};
