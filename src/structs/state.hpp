#ifndef STATE
#define STATE

#include <glm/glm.hpp>

struct State {
	glm::vec3 position = glm::vec3(0, 0, 0);

	glm::vec4 direction = glm::vec4(0, 0, 1, 0); // along z-axis, points backwards
	glm::vec4 right = glm::vec4(1, 0, 0, 0); // along x-axis
	glm::vec4 up = glm::vec4(0, 1, 0, 0); // along y-axis

	glm::vec3 velocity = glm::vec3(0, 0, 0); // in local coordinates

	glm::vec3 angVelocityDeg = glm::vec3(0, 0, 0); // in local coordinates
};

#endif
