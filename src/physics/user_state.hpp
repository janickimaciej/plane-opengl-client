#pragma once

#include "common/airplane_type_name.hpp"
#include "common/state.hpp"

namespace Physics
{
	struct UserState
	{
		int hp{};
		Common::State state{};
		Common::AirplaneTypeName airplaneTypeName;
	};
};
