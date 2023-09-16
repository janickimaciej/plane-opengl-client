#include "physics/model_dynamics/rigid_body_dynamics.hpp"

#include "physics/runge_kutta.hpp"
#include "state.hpp"
#include "time.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

RigidBodyDynamics::RigidBodyDynamics(float mass, const glm::mat3& momentOfInertia) :
	m_mass{mass},
	m_momentOfInertia{momentOfInertia},
	m_momentOfInertiaInverse{glm::inverse(momentOfInertia)}
{ }

void RigidBodyDynamics::rightHandSide(float, const std::array<float, State::stateLength>& state,
	std::array<float, State::stateLength>& stateDerivative) const
{
	State stateObj{};
	State::arrToObj(state, stateObj);
	State stateDerivativeObj{};

	glm::vec3 netForce{};
	glm::vec3 netTorque{};
	computeNetForceAndNetTorque(stateObj, netForce, netTorque);

	glm::mat3 rotateMatrix{State::objToMat(stateObj)};
	stateDerivativeObj.position = rotateMatrix * stateObj.velocity;

	glm::vec3 angVelocityGlobalRad = rotateMatrix * stateObj.angVelocityRad;
	stateDerivativeObj.right = glm::cross(angVelocityGlobalRad, stateObj.right);
	stateDerivativeObj.up = glm::cross(angVelocityGlobalRad, stateObj.up);
	stateDerivativeObj.direction = glm::cross(angVelocityGlobalRad, stateObj.direction);

	stateDerivativeObj.velocity = netForce / m_mass - glm::cross(stateObj.angVelocityRad,
		stateObj.velocity);

	stateDerivativeObj.angVelocityRad = m_momentOfInertiaInverse * (netTorque -
		glm::cross(stateObj.angVelocityRad, m_momentOfInertia * stateObj.angVelocityRad));

	State::objToArr(stateDerivativeObj, stateDerivative);
}

State RigidBodyDynamics::computeNewState(const State& oldState) const
{
	std::array<float, State::stateLength> oldStateArr{};
	State::objToArr(oldState, oldStateArr);
	
	std::array<float, State::stateLength> newStateArr{};
	RungeKutta<State::stateLength>::RK4(0, Time::getDeltaTime(), oldStateArr, *this, newStateArr);

	State newState{};
	State::arrToObj(newStateArr, newState);
	State::normalize(newState);

	return newState;
}
