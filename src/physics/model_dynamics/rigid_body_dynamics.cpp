#include "physics/model_dynamics/rigid_body_dynamics.hpp"

#include "physics/runge_kutta.hpp"
#include "state.hpp"
#include "time.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <array>

RigidBodyDynamics::RigidBodyDynamics(float mass, const glm::mat3& momentOfInertia) :
	m_mass{mass},
	m_momentOfInertia{momentOfInertia},
	m_momentOfInertiaInverse{glm::inverse(momentOfInertia)}
{ }

void RigidBodyDynamics::rightHandSide(float, const std::array<float, State::stateLength>& state,
	std::array<float, State::stateLength>& stateDerivative) const
{
	State stateObj{state};
	State stateDerivativeObj{};

	glm::vec3 netForce{};
	glm::vec3 netTorque{};
	computeNetForceAndNetTorque(stateObj, netForce, netTorque);

	stateDerivativeObj.position = stateObj.orientation * stateObj.velocity;

	stateDerivativeObj.orientation = stateObj.orientation * glm::quat{0, stateObj.angVelocityRad} /
		(float)2;

	stateDerivativeObj.velocity = netForce / m_mass - glm::cross(stateObj.angVelocityRad,
		stateObj.velocity);

	stateDerivativeObj.angVelocityRad = m_momentOfInertiaInverse * (netTorque -
		glm::cross(stateObj.angVelocityRad, m_momentOfInertia * stateObj.angVelocityRad));

	stateDerivativeObj.toArr(stateDerivative);
}

State RigidBodyDynamics::computeNewState(const State& oldState) const
{
	std::array<float, State::stateLength> oldStateArr{};
	oldState.toArr(oldStateArr);
	
	std::array<float, State::stateLength> newStateArr{};
	RungeKutta<State::stateLength>::RK4(0, Time::getDeltaTime(), oldStateArr, *this, newStateArr);

	State newState{newStateArr};
	newState.normalize();

	return newState;
}
