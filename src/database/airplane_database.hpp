#pragma once

#include "airplane_type.hpp"
#include "graphics/paths.hpp"

#include <array>

constexpr int airplaneTypeCount = 1;

enum class AirplaneTypeName
{
	mustang
};

extern const AirplaneParams mustangParams;

const std::array<AirplaneType, airplaneTypeCount> airplaneTypes
{
	{
		mustangParams,
		T_CAMO,
		SM_AIRPLANE_CAP,
		SM_AIRPLANE_PROPELLER,
		SM_AIRPLANE_BODY,
		SM_AIRPLANE_JOINS,
		SM_AIRPLANE_TIRES,
		SM_AIRPLANE_LIGHT
	}
};
