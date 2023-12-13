#pragma once

#include <cstdint>

namespace Common
{
	inline constexpr int airplaneTypeCount = 1;

	enum class AirplaneTypeName
	{
		mustang
	};

	unsigned char toUChar(AirplaneTypeName airplaneTypeName);
};
