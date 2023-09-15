#include "model_dynamics/airplane_dynamics.hpp"

#include "flight_ctrl.hpp"
#include "model_dynamics/rigid_body_dynamics.hpp"
#include "structs/airplane_params.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

AirplaneDynamics::AirplaneDynamics(const AirplaneParams& params,
	const FlightCtrl& flightCtrl) :
	RigidBodyDynamics{params.mass, params.momentOfInertia},
	m_params{params},
	m_flightCtrl{flightCtrl}
{ }

void AirplaneDynamics::computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{
	constexpr float g = 9.81f;

	glm::mat3 rotateMatrixInverse = glm::inverse(glm::mat3{State::objToMat(state)});
	glm::vec3 gravityForce{0, -m_params.mass * g, 0};
	netForce = glm::vec3{rotateMatrixInverse * glm::vec4{gravityForce, 0}};
	netTorque = glm::vec3{0, 0, 0};

	netForce = glm::vec3{0, 0, 0}; //tmp
	netTorque = glm::vec3{0, 0, 0}; //tmp
}
