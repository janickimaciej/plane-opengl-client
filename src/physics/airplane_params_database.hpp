#pragma once

#include "common/airplane_type_name.hpp"
#include "physics/airplane_params/airplane_params.hpp"

#include <array>

namespace Physics
{
	extern const AirplaneParams mustangParams;

	inline const std::array<AirplaneParams, Common::airplaneTypeCount> airplaneParamsDatabase
	{
		mustangParams
	};
};
