#include "model_dynamics/airplane_dynamics.hpp"

#include "flight_control.hpp"
#include "model_dynamics/rigid_body_dynamics.hpp"
#include "structs/airplane_parameters.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

AirplaneDynamics::AirplaneDynamics(const AirplaneParameters& parameters,
	const FlightControl& flightControl) :
	RigidBodyDynamics { parameters.mass, parameters.momentOfInertia },
	m_parameters { parameters },
	m_flightControl { flightControl }
{ }

void AirplaneDynamics::computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{
	/*netForce = glm::vec3 { 0, 200000, 0 };
	netTorque = glm::vec3 { 0, 0, 0 };*/

	glm::vec3 gravityForce { 0, -10, 0 };
	glm::vec3 leverArm { 0, 0, 1 };
	netForce = glm::vec3 { 0, 0, 0 };
	netTorque = glm::cross(leverArm, glm::vec3 { glm::inverse(State::objectToMatrix(state)) *
		glm::vec4 { -gravityForce, 0 } });
}
