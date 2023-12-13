#pragma once

#include "common/user_info.hpp"

namespace Physics
{
	struct SimulationBufferUser
	{
		unsigned int second{};
		Common::UserInfo info{};
	};
};
