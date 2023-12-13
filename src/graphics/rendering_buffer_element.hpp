#pragma once

#include "common/airplane_info.hpp"

#include <unordered_map>

namespace Graphics
{
	struct RenderingBufferElement
	{
		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos{};
		int day{};
		float timeOfDay{};
	};
};
