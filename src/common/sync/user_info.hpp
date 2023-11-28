#pragma once

#include "common/sync/user_input.hpp"
#include "common/sync/user_state.hpp"

namespace Common
{
	struct UserInfo
	{
		int second{};
		UserInput input{};
		UserState state{};
	};
};
