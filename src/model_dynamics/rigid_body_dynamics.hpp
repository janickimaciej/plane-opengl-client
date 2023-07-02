#ifndef RIGID_BODY_DYNAMICS
#define RIGID_BODY_DYNAMICS

#include "../runge_kutta_right_hand_side.hpp"
#include "../structs/state.hpp"

class RigidBodyDynamics : RungeKuttaRightHandSide {
	float mass;
	glm::mat3 momentOfInertia;
	glm::mat3 momentOfInertiaInverse;

	virtual void computeNetForceAndNetTorque(State state, glm::vec3* netForce,
		glm::vec3* netTorque) const = 0;
public:
	RigidBodyDynamics(float mass, glm::mat3 momentOfInertia);
	virtual void rightHandSide(float time, const float stateArray[], float stateDerivativeArray[]) const override;
	State computeNewState(State oldState);
	virtual ~RigidBodyDynamics() = default;
};

#endif
