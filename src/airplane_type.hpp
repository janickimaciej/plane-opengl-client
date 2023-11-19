#pragma once

#include "physics/airplane_params/airplane_params.hpp"

#include <string>

struct AirplaneType
{
	AirplaneParams params;
	const std::string camo;
	const std::string cap;
	const std::string propeller;
	const std::string body;
	const std::string joins;
	const std::string tires;
	const std::string light;
};
