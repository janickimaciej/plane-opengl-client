#ifndef STATE
#define STATE

#include <glm/glm.hpp>

struct State {
	static const unsigned int stateLength = 18;

	glm::vec3 position = glm::vec3(0, 0, 0);

	glm::vec3 right = glm::vec3(1, 0, 0); // along x-axis
	glm::vec3 up = glm::vec3(0, 1, 0); // along y-axis
	glm::vec3 direction = glm::vec3(0, 0, 1); // along z-axis

	glm::vec3 velocity = glm::vec3(0, 0, 0); // in local coordinates

	glm::vec3 angVelocityRad = glm::vec3(0, 0, 0); // in local coordinates

	static void objectToArray(const State state, float stateArray[]);
	static void arrayToObject(const float stateArray[], State* state);
};

#endif
