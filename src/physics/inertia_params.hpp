#ifndef INERTIA_PARAMS_HPP
#define INERTIA_PARAMS_HPP

#include <glm/glm.hpp>

struct InertiaParams
{
	float mass{};
	glm::mat3 momentOfInertia{};
	glm::vec3 nosePosition{};
};

#endif
