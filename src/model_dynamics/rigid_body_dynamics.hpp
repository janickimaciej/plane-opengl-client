#ifndef RIGID_BODY_DYNAMICS_HPP
#define RIGID_BODY_DYNAMICS_HPP

#include "runge_kutta_right_hand_side.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

#include <array>

class RigidBodyDynamics : public RungeKuttaRightHandSide<State::stateLength>
{
public:
	RigidBodyDynamics(float mass, const glm::mat3& momentOfInertia);
	virtual void rightHandSide(float, const std::array<float, State::stateLength>& state,
		std::array<float, State::stateLength>& stateDerivative) const override;
	State computeNewState(const State& oldState) const;
	virtual ~RigidBodyDynamics() = default;

private:
	float m_mass {};
	glm::mat3 m_momentOfInertia {};
	glm::mat3 m_momentOfInertiaInverse {};

	virtual void computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
		glm::vec3& netTorque) const = 0;
};

#endif
