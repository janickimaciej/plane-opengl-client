#pragma once

#include "common/airplane_type_name.hpp"
#include "common/state.hpp"

namespace Common
{
	struct UserState
	{
		int hp{};
		State state{};
		AirplaneTypeName airplaneTypeName;
	};
};
