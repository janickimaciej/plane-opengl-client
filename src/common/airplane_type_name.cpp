#include "common/airplane_type_name.hpp"

#include <cstdint>

namespace Common
{
	unsigned char toUChar(AirplaneTypeName airplaneTypeName)
	{
		return static_cast<uint8_t>(airplaneTypeName);
	}
};
