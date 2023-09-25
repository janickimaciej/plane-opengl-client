#include "physics/atmosphere.hpp"

#include <algorithm>

float Atmosphere::airDensity(float height)
{
	static constexpr float zeroAirDensityHeight = 44300;
	return std::max(seaLevelAirDensity * (1 - height/zeroAirDensityHeight), (float)0);
}