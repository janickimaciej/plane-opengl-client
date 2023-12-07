#pragma once

#include "common/airplane_type_name.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/airplane_params_database/mustang.hpp"

#include <array>

namespace Physics
{
	inline const std::array<AirplaneParams, Common::airplaneTypeCount> airplaneParamsDatabase
	{
		mustangParams
	};
};
