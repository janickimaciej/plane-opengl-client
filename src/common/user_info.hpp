#pragma once

#include "common/user_input.hpp"
#include "common/user_state.hpp"

namespace Common
{
	struct UserInfo
	{
		UserInput input{};
		UserState state{};
	};
};
