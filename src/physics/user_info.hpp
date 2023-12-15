#pragma once

#include "physics/user_input.hpp"
#include "physics/user_state.hpp"

namespace Physics
{
	struct UserInfo
	{
		UserInput input{};
		UserState state{};
	};
};
