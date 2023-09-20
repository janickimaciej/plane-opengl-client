#include "physics/model_dynamics/airplane_dynamics.hpp"

#include "physics/airplane_params.hpp"
#include "physics/atmosphere.hpp"
#include "physics/inertia_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/fuselage_params.hpp"
#include "physics/model_dynamics/rigid_body_dynamics.hpp"
#include "physics/propulsion_params.hpp"
#include "physics/surface_params.hpp"
#include "state.hpp"

#include <glm/glm.hpp>

namespace
{
	constexpr float eps = 1e-9;
}

AirplaneDynamics::AirplaneDynamics(const AirplaneParams& params,
	const FlightCtrl& flightCtrl) :
	RigidBodyDynamics{params.inertia.mass, params.inertia.momentOfInertia},
	m_params{params},
	m_flightCtrl{flightCtrl}
{ }

void AirplaneDynamics::computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{
	netForce = glm::vec3{0, 0, 0};
	netTorque = glm::vec3{0, 0, 0};

	addForceAndTorqueInertia(state, netForce, netTorque);
	addForceAndTorqueSurface(state, netForce, netTorque);
	addForceAndTorqueFuselage(state, netForce, netTorque);
	addForceAndTorquePropulsion(state, netForce, netTorque);
}

void AirplaneDynamics::addForceAndTorqueInertia(const State& state, glm::vec3& netForce,
	glm::vec3&) const
{
	static constexpr float g = 9.81f;

	glm::vec3 gravityGlobal{0, -m_params.inertia.mass * g, 0};
	glm::mat3 rotateMatrixInverse = glm::inverse(glm::mat3{State::objToMat(state)});
	netForce += rotateMatrixInverse * gravityGlobal;
}

void AirplaneDynamics::addForceAndTorqueSurface(const State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{

}

void AirplaneDynamics::addForceAndTorqueFuselage(const State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{
	float airDensity = Atmosphere::airDensity(state.position.y);

	glm::vec3 airVelocity = computeAirVelocity(state, m_params.fuselage.frontDragPoint);
	if (airVelocity.z > eps)
	{
		float dynamicPressure = airDensity * airVelocity.z * airVelocity.z / 2;
		glm::vec3 frontDrag{0, 0, 0};
		frontDrag = dynamicPressure * m_params.fuselage.frontArea *
			m_params.fuselage.frontDragCoef * glm::vec3{0, 0, 1};
		netForce += frontDrag;
		netTorque += glm::cross(m_params.fuselage.frontDragPoint, frontDrag);
	}

	airVelocity = computeAirVelocity(state, m_params.fuselage.sideDragPoint);
	glm::vec3 sideAirVelocity = glm::vec3{airVelocity.x, airVelocity.y, 0};
	float sideAirSpeed = glm::length(sideAirVelocity);
	if (sideAirSpeed > eps)
	{
		float dynamicPressure = airDensity * sideAirSpeed * sideAirSpeed / 2;
		glm::vec3 sideDrag = dynamicPressure * m_params.fuselage.sideArea *
			m_params.fuselage.sideDragCoef * sideAirVelocity / sideAirSpeed;
		netForce += sideDrag;
		netTorque += glm::cross(m_params.fuselage.sideDragPoint, sideDrag);
	}
}

void AirplaneDynamics::addForceAndTorquePropulsion(const State& state, glm::vec3& netForce,
	glm::vec3& netTorque) const
{
	glm::vec3 thrust = m_flightCtrl.getThrustRelative() * Atmosphere::airDensity(state.position.y) /
		Atmosphere::seaLevelAirDensity * m_params.propulsion.maxThrust * glm::vec3{0, 0, -1};
	netForce += thrust;
}

glm::vec3 AirplaneDynamics::computeAirVelocity(const State& state, const glm::vec3& point) const
{
	return -state.velocity + glm::cross(point, state.angVelocityRad);
}
