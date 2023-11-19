#pragma once

#include <glm/glm.hpp>

struct InertiaParams
{
	float mass{};
	glm::mat3 momentOfInertia{};
	glm::vec3 nosePosition{};
};
