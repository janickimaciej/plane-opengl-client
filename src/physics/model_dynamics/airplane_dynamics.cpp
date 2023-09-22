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
	constexpr float eps = 1e-9f;
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

	addForceAndTorqueInertia(state, m_params.inertia, netForce, netTorque);
	/*addForceAndTorqueSurface(state, m_params.hStab, m_flightCtrl.getElevatorAngleRad(), netForce,
		netTorque);
	addForceAndTorqueSurface(state, m_params.vStab, m_flightCtrl.getRudderAngleRad(), netForce,
		netTorque);*/
	addForceAndTorqueSurface(state, m_params.leftWing, -m_flightCtrl.getAileronsAngleRad(),
		netForce, netTorque);
	addForceAndTorqueSurface(state, m_params.rightWing, m_flightCtrl.getAileronsAngleRad(),
		netForce, netTorque);
	addForceAndTorqueFuselage(state, m_params.fuselage, netForce, netTorque);
	addForceAndTorquePropulsion(state, m_params.propulsion, m_flightCtrl.getThrustRelative(),
		netForce, netTorque);
}

void AirplaneDynamics::addForceAndTorqueInertia(const State& state, const InertiaParams& params,
	glm::vec3& netForce, glm::vec3&)
{
	static constexpr float g = 9.81f;

	glm::vec3 gravityGlobal{0, -params.mass * g, 0};
	glm::mat3 rotateMatrixInverse = glm::inverse(glm::mat3{State::objToMat(state)});
	netForce += rotateMatrixInverse * gravityGlobal;
}

void AirplaneDynamics::addForceAndTorqueSurface(const State& state, const SurfaceParams& params,
	float ctrlAngleRad, glm::vec3& netForce, glm::vec3& netTorque)
{
	float airDensity = Atmosphere::airDensity(state.position.y);

	glm::vec3 airVelocity = computeAirVelocity(state, params.liftPoint);
	if(glm::abs(airVelocity.z) > eps)
	{
		glm::vec3 yzAirVelocity = glm::vec3{0, airVelocity.y, airVelocity.z};
		float yzAirSpeed = glm::length(yzAirVelocity);
		float angleOfAttackRad = glm::atan(yzAirVelocity.y, yzAirVelocity.z);
		if (yzAirSpeed > eps && angleOfAttackRad > -params.criticalAngleRad &&
			angleOfAttackRad < params.criticalAngleRad)
		{
			float dynamicPressure = airDensity * yzAirSpeed * yzAirSpeed / 2;
			float liftCoef = params.liftCoefConst + params.liftCoefDeriv * angleOfAttackRad;
			float ctrlLiftCoef = -params.ctrlLiftCoefDeriv * ctrlAngleRad;
			glm::vec3 liftDirection = glm::normalize(glm::cross(yzAirVelocity, glm::vec3{1, 0, 0}));
			glm::vec3 lift = dynamicPressure * (params.area * liftCoef + params.ctrlArea *
				ctrlLiftCoef) * liftDirection;
			netForce += lift;
			netTorque += glm::cross(params.liftPoint, lift);
		}
	}
}

void AirplaneDynamics::addForceAndTorqueFuselage(const State& state, const FuselageParams& params,
	glm::vec3& netForce, glm::vec3& netTorque)
{
	float airDensity = Atmosphere::airDensity(state.position.y);

	glm::vec3 airVelocity = computeAirVelocity(state, params.frontDragPoint);
	if (glm::abs(airVelocity.z) > eps)
	{
		float dynamicPressure = airDensity * airVelocity.z * airVelocity.z / 2;
		glm::vec3 frontDrag = dynamicPressure * params.frontArea * params.frontDragCoef *
			glm::vec3{0, 0, airVelocity.z > 0 ? 1 : -1};
		netForce += frontDrag;
		netTorque += glm::cross(params.frontDragPoint, frontDrag);
	}

	airVelocity = computeAirVelocity(state, params.sideDragPoint);
	glm::vec3 xyAirVelocity = glm::vec3{airVelocity.x, airVelocity.y, 0};
	float xyAirSpeed = glm::length(xyAirVelocity);
	if (xyAirSpeed > eps)
	{
		float dynamicPressure = airDensity * xyAirSpeed * xyAirSpeed / 2;
		glm::vec3 sideDrag = dynamicPressure * params.sideArea * params.sideDragCoef *
			xyAirVelocity / xyAirSpeed;
		netForce += sideDrag;
		netTorque += glm::cross(params.sideDragPoint, sideDrag);
	}
}

void AirplaneDynamics::addForceAndTorquePropulsion(const State& state,
	const PropulsionParams& params, float thrustRelative, glm::vec3& netForce,
	glm::vec3&)
{
	glm::vec3 thrust = thrustRelative * Atmosphere::airDensity(state.position.y) /
		Atmosphere::seaLevelAirDensity * params.maxThrust * glm::vec3{0, 0, -1};
	netForce += thrust;
}

glm::vec3 AirplaneDynamics::computeAirVelocity(const State& state, const glm::vec3& point)
{
	return -state.velocity + glm::cross(point, state.angVelocityRad);
}
