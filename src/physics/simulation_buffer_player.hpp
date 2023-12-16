#pragma once

#include "physics/player_info.hpp"

#include <array>

namespace Physics
{
	struct SimulationBufferPlayer
	{
		std::array<bool, 2> hasControlFrame{};
		PlayerInfo info{};
	};
};
