#pragma once

#include "common/airplane_type_name.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Graphics
{
	inline constexpr std::array<glm::vec3, Common::airplaneTypeCount> airplaneCameraPositions
	{
		glm::vec3{0, 5, 16},
		glm::vec3{0, 10, 25}
	};
};
