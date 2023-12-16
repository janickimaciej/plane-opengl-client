#pragma once

#include "physics/player_input.hpp"
#include "physics/player_state.hpp"

namespace Physics
{
	struct PlayerInfo
	{
		PlayerInput input{};
		PlayerState state{};
	};
};
