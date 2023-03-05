#include "state.hpp"

void State::objectToArray(const State state, float stateArray[]) {
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

void State::arrayToObject(const float stateArray[], State* state) {
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
