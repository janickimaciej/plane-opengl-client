#include "model_dynamics/rigid_body_dynamics.hpp"

#include "runge_kutta.hpp"
#include "structs/state.hpp"
#include "time.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

RigidBodyDynamics::RigidBodyDynamics(float mass, glm::mat3 momentOfInertia) :
	m_mass { mass },
	m_momentOfInertia { momentOfInertia },
	m_momentOfInertiaInverse { glm::inverse(momentOfInertia) }
{ }

void RigidBodyDynamics::rightHandSide(float time, const float stateArray[],
	float stateDerivativeArray[]) const
{
	State state {};
	State::arrayToObject(stateArray, &state);
	State stateDerivative {};

	glm::vec3 netForce {};
	glm::vec3 netTorque {};
	computeNetForceAndNetTorque(state, &netForce, &netTorque);

	float rotateMatrixT[9]
	{
		state.right.x, state.right.y, state.right.z,
		state.up.x, state.up.y, state.up.z,
		state.direction.x, state.direction.y, state.direction.z
	};
	glm::mat3 rotateMatrix = glm::make_mat3(rotateMatrixT);
	stateDerivative.position = rotateMatrix * state.velocity;

	glm::vec3 angVelocityGlobalRad = rotateMatrix * state.angVelocityRad;
	stateDerivative.right = glm::cross(angVelocityGlobalRad, state.right);
	stateDerivative.up = glm::cross(angVelocityGlobalRad, state.up);
	stateDerivative.direction = glm::cross(angVelocityGlobalRad, state.direction);

	stateDerivative.velocity = netForce / m_mass - glm::cross(state.angVelocityRad, state.velocity);

	stateDerivative.angVelocityRad = m_momentOfInertiaInverse * (netTorque -
		glm::cross(state.angVelocityRad, m_momentOfInertia * state.angVelocityRad));

	State::objectToArray(stateDerivative, stateDerivativeArray);
}

State RigidBodyDynamics::computeNewState(State oldState) const
{
	float oldStateArray[State::stateLength] {};
	State::objectToArray(oldState, oldStateArray);
	
	float newStateArray[State::stateLength] {};
	RungeKutta::RK4(State::stateLength, 0, Time::getDeltaTime(), oldStateArray, *this,
		newStateArray);

	State newState {};
	State::arrayToObject(newStateArray, &newState);
	State::normalize(newState);

	return newState;
}
