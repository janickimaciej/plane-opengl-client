#include "rigid_body_dynamics.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../runge_kutta.hpp"
#include "../time.hpp"

RigidBodyDynamics::RigidBodyDynamics(float mass, glm::mat3 momentOfInertia) : mass(mass),
	momentOfInertia(momentOfInertia), momentOfInertiaInverse(glm::inverse(momentOfInertia)) { }

void RigidBodyDynamics::rightHandSide(float time, const float stateArray[], float resultArray[]) const {
	State state;
	State::arrayToObject(stateArray, &state);
	State result;

	glm::vec3 netForce;
	glm::vec3 netTorque;
	computeNetForceAndNetTorque(state, &netForce, &netTorque);

	float rotateMatrixT[9] = {
		state.right.x, state.right.y, state.right.z,
		state.up.x, state.up.y, state.up.z,
		state.direction.x, state.direction.y, state.direction.z
	};
	glm::mat3 rotateMatrix = glm::make_mat3(rotateMatrixT);
	result.position = rotateMatrix*state.velocity;

	glm::vec3 angVelocityGlobalRad = rotateMatrix*state.angVelocityRad;
	result.right = glm::cross(angVelocityGlobalRad, state.right);
	result.up = glm::cross(angVelocityGlobalRad, state.up);
	result.direction = glm::cross(angVelocityGlobalRad, state.direction);

	result.velocity = netForce/mass - glm::cross(state.angVelocityRad, state.velocity);

	result.angVelocityRad = momentOfInertiaInverse*(netTorque -
		glm::cross(state.angVelocityRad, momentOfInertia*state.angVelocityRad));

	State::objectToArray(result, resultArray);
}

State RigidBodyDynamics::computeNewState(State oldState) {
	float oldStateArray[State::stateLength];
	State::objectToArray(oldState, oldStateArray);
	
	float newStateArray[State::stateLength];
	RungeKutta::RK4(State::stateLength, 0, Time::getDeltaTime(), oldStateArray, *this, newStateArray);

	State newState;
	State::arrayToObject(newStateArray, &newState);
	return newState;
}
