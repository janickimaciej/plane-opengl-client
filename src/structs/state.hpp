#ifndef STATE_HPP
#define STATE_HPP

#include <glm/glm.hpp>

struct State
{
	static constexpr unsigned int stateLength = 18;

	glm::vec3 position { 0, 0, 0 };

	glm::vec3 right { 1, 0, 0 }; // along x-axis
	glm::vec3 up { 0, 1, 0 }; // along y-axis
	glm::vec3 direction { 0, 0, 1 }; // along z-axis

	glm::vec3 velocity { 0, 0, 0 }; // in local coordinates

	glm::vec3 angVelocityRad { 0, 0, 0 }; // in local coordinates

	static glm::mat4 objectToMatrix(const State state);
	static void normalize(State& state);
	static void objectToArray(const State& state, float stateArray[]);
	static void arrayToObject(const float stateArray[], State* state);
};

#endif
