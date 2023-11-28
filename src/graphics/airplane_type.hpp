#pragma once

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	struct AirplaneType
	{
		glm::vec3 nosePosition{};
		const std::string camo;
		const std::string cap;
		const std::string propeller;
		const std::string body;
		const std::string joins;
		const std::string tires;
		const std::string light;
	};
};
