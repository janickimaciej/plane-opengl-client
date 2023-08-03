#ifndef RIGID_BODY_DYNAMICS_HPP
#define RIGID_BODY_DYNAMICS_HPP

#include "runge_kutta_right_hand_side.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

class RigidBodyDynamics : RungeKuttaRightHandSide
{
public:
	RigidBodyDynamics(float mass, glm::mat3 momentOfInertia);
	virtual void rightHandSide(float time, const float stateArray[], float stateDerivativeArray[])
		const override;
	State computeNewState(State oldState) const;
	virtual ~RigidBodyDynamics() = default;

private:
	float m_mass {};
	glm::mat3 m_momentOfInertia {};
	glm::mat3 m_momentOfInertiaInverse {};

	virtual void computeNetForceAndNetTorque(State state, glm::vec3* netForce, glm::vec3* netTorque)
		const = 0;
};

#endif
