#ifndef AIRPLANE_DYNAMICS
#define AIRPLANE_DYNAMICS

#include "rigid_body_dynamics.hpp"
#include "../flight_control.hpp"
#include "../structs/airplane_parameters.hpp"

class AirplaneDynamics : RigidBodyDynamics {
	const AirplaneParameters parameters;
	const FlightControl& flightControl;

	virtual void computeNetForceAndNetTorque(State state, glm::vec3* netForce,
		glm::vec3* netTorque) const override;
public:
	AirplaneDynamics(float mass, glm::mat3 momentOfInertia,
		AirplaneParameters parameters, const FlightControl& flightControl);
	virtual ~AirplaneDynamics() = default;
};

#endif
