#include "airplane_dynamics.hpp"

void AirplaneDynamics::computeNetForceAndNetTorque(State state, glm::vec3* netForce,
	glm::vec3* netTorque) const {
	//TODO
}

AirplaneDynamics::AirplaneDynamics(float mass, glm::mat3 momentOfInertia,
	AirplaneParameters parameters, const FlightControl& flightControl) :
	RigidBodyDynamics(mass, momentOfInertia), parameters(parameters),
	flightControl(flightControl) { }