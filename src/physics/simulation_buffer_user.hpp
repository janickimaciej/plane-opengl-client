#pragma once

#include "physics/user_info.hpp"

#include <array>

namespace Physics
{
	struct SimulationBufferUser
	{
		std::array<bool, 2> hasControlFrame{};
		UserInfo info{};
	};
};
