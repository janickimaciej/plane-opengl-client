#pragma once

#include "common/airplane_type_name.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Common
{
	constexpr std::array<glm::vec3, airplaneTypeCount> airplaneCenterOfMassDatabase
	{
		glm::vec3{0, 0, 4.05f}
	};
};
