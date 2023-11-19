#pragma once

#include "sync/user_input.hpp"
#include "sync/user_state.hpp"

struct UserInfo
{
	int second{};
	UserInput input{};
	UserState state{};
};
