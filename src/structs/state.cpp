#include "structs/state.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 State::objectToMatrix(const State state)
{
	float rotateMatrixT[16]
	{
		state.right.x, state.right.y, state.right.z, 0,
		state.up.x, state.up.y, state.up.z, 0,
		state.direction.x, state.direction.y, state.direction.z, 0,
		0, 0, 0, 1
	};
	glm::mat4 rotateMatrix = glm::make_mat4(rotateMatrixT);

	glm::mat4 translateMatrix = glm::translate(glm::mat4 { 1 }, state.position);

	return translateMatrix * rotateMatrix;
}

void State::normalize(State& state)
{
	state.right = glm::normalize(state.right);
	state.up = glm::normalize(state.up);
	state.direction = glm::cross(state.right, state.up);
	state.up = glm::cross(state.direction, state.right);
}

void State::objectToArray(const State& state, float stateArray[])
{
	stateArray[0] = state.position.x;
	stateArray[1] = state.position.y;
	stateArray[2] = state.position.z;
	stateArray[3] = state.right.x;
	stateArray[4] = state.right.y;
	stateArray[5] = state.right.z;
	stateArray[6] = state.up.x;
	stateArray[7] = state.up.y;
	stateArray[8] = state.up.z;
	stateArray[9] = state.direction.x;
	stateArray[10] = state.direction.y;
	stateArray[11] = state.direction.z;
	stateArray[12] = state.velocity.x;
	stateArray[13] = state.velocity.y;
	stateArray[14] = state.velocity.z;
	stateArray[15] = state.angVelocityRad.x;
	stateArray[16] = state.angVelocityRad.y;
	stateArray[17] = state.angVelocityRad.z;
}

void State::arrayToObject(const float stateArray[], State* state)
{
	state->position.x = stateArray[0];
	state->position.y = stateArray[1];
	state->position.z = stateArray[2];
	state->right.x = stateArray[3];
	state->right.y = stateArray[4];
	state->right.z = stateArray[5];
	state->up.x = stateArray[6];
	state->up.y = stateArray[7];
	state->up.z = stateArray[8];
	state->direction.x = stateArray[9];
	state->direction.y = stateArray[10];
	state->direction.z = stateArray[11];
	state->velocity.x = stateArray[12];
	state->velocity.y = stateArray[13];
	state->velocity.z = stateArray[14];
	state->angVelocityRad.x = stateArray[15];
	state->angVelocityRad.y = stateArray[16];
	state->angVelocityRad.z = stateArray[17];
}
