#include "structs/state.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

glm::mat4 State::objectToMatrix(const State& state)
{
	const float rotateMatrixT[16]
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

void State::objToArr(const State& stateObj, std::array<float, stateLength>& stateVec)
{
	stateVec[0] = stateObj.position.x;
	stateVec[1] = stateObj.position.y;
	stateVec[2] = stateObj.position.z;
	stateVec[3] = stateObj.right.x;
	stateVec[4] = stateObj.right.y;
	stateVec[5] = stateObj.right.z;
	stateVec[6] = stateObj.up.x;
	stateVec[7] = stateObj.up.y;
	stateVec[8] = stateObj.up.z;
	stateVec[9] = stateObj.direction.x;
	stateVec[10] = stateObj.direction.y;
	stateVec[11] = stateObj.direction.z;
	stateVec[12] = stateObj.velocity.x;
	stateVec[13] = stateObj.velocity.y;
	stateVec[14] = stateObj.velocity.z;
	stateVec[15] = stateObj.angVelocityRad.x;
	stateVec[16] = stateObj.angVelocityRad.y;
	stateVec[17] = stateObj.angVelocityRad.z;
}

void State::arrToObj(const std::array<float, stateLength>& stateArr, State& state)
{
	state.position.x = stateArr[0];
	state.position.y = stateArr[1];
	state.position.z = stateArr[2];
	state.right.x = stateArr[3];
	state.right.y = stateArr[4];
	state.right.z = stateArr[5];
	state.up.x = stateArr[6];
	state.up.y = stateArr[7];
	state.up.z = stateArr[8];
	state.direction.x = stateArr[9];
	state.direction.y = stateArr[10];
	state.direction.z = stateArr[11];
	state.velocity.x = stateArr[12];
	state.velocity.y = stateArr[13];
	state.velocity.z = stateArr[14];
	state.angVelocityRad.x = stateArr[15];
	state.angVelocityRad.y = stateArr[16];
	state.angVelocityRad.z = stateArr[17];
}
