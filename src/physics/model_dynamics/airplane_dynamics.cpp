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

	addForceAndTorque(state, m_params.inertia, netForce, netTorque);
	addForceAndTorque(state, m_params.hStab, m_flightCtrl.getElevatorAngleRad(), netForce,
		netTorque);
	addForceAndTorque(state, m_params.vStab, m_flightCtrl.getRudderAngleRad(), netForce,
		netTorque);
	addForceAndTorque(state, m_params.leftWing, -m_flightCtrl.getAileronsAngleRad(),
		netForce, netTorque);
	addForceAndTorque(state, m_params.rightWing, m_flightCtrl.getAileronsAngleRad(),
		netForce, netTorque);
	addForceAndTorque(state, m_params.fuselage, netForce, netTorque);
	addForceAndTorque(state, m_params.propulsion, m_flightCtrl.getThrustRelative(),
		netForce, netTorque);
}

void AirplaneDynamics::addForceAndTorque(const State& state, const InertiaParams& params,
	glm::vec3& netForce, glm::vec3&)
{
	static constexpr float g = 9.81f;

	glm::vec3 gravityGlobal{0, -params.mass * g, 0};
	glm::mat3 rotateMatrixInverse = glm::inverse(glm::mat3{State::objToMat(state)});
	netForce += rotateMatrixInverse * gravityGlobal;
}

void AirplaneDynamics::addForceAndTorque(const State& state, const SurfaceParams& params,
	float ctrlAngleRad, glm::vec3& netForce, glm::vec3& netTorque)
{
	float airDensity = Atmosphere::airDensity(state.position.y);

	glm::vec3 airVelocity = computeAirVelocity(state, params.liftPoint);
	glm::vec3 airVelocitySurface = params.orientationInverse * airVelocity;
	glm::vec3 yzAirVelocitySurface = glm::vec3{0, airVelocitySurface.y, airVelocitySurface.z};
	float yzAirSpeed = glm::length(yzAirVelocitySurface);
	float angleOfAttackRad = glm::atan(yzAirVelocitySurface.y, yzAirVelocitySurface.z);
	if (yzAirSpeed > eps && angleOfAttackRad > params.criticalAngleNegativeRad &&
		angleOfAttackRad < params.criticalAnglePositiveRad)
	{
		float dynamicPressure = airDensity * yzAirSpeed * yzAirSpeed / 2;
		float liftCoef = params.liftCoefConst + params.liftCoefDeriv * angleOfAttackRad;
		float ctrlLiftCoef = -params.ctrlLiftCoefDeriv * ctrlAngleRad;
		glm::vec3 liftDirectionSurface = glm::normalize(glm::cross(yzAirVelocitySurface,
			glm::vec3{1, 0, 0}));
		glm::vec3 liftSurface = dynamicPressure * (params.area * liftCoef + params.ctrlArea *
			ctrlLiftCoef) * liftDirectionSurface;
		glm::vec3 lift = params.orientation * liftSurface;
		netForce += lift;
		netTorque += glm::cross(params.liftPoint, lift);
	}

	airVelocity = computeAirVelocity(state, params.normalForcePoint);
	airVelocitySurface = params.orientationInverse * airVelocity;
	if (glm::abs(airVelocitySurface.y) > eps)
	{
		float dynamicPressure = airDensity * airVelocitySurface.y * airVelocitySurface.y / 2;
		glm::vec3 normalForceSurface = dynamicPressure * params.area * params.normalForceCoef *
			glm::vec3{0, airVelocitySurface.y > 0 ? 1 : -1, 0};
		glm::vec3 normalForce = params.orientation * normalForceSurface;
		netForce += normalForce;
		netTorque += glm::cross(params.normalForcePoint, normalForce);
	}
}

void AirplaneDynamics::addForceAndTorque(const State& state, const FuselageParams& params,
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

void AirplaneDynamics::addForceAndTorque(const State& state, const PropulsionParams& params,
	float thrustRelative, glm::vec3& netForce, glm::vec3& netTorque)
{
	float airDensityRelative = Atmosphere::airDensity(state.position.y) /
		Atmosphere::seaLevelAirDensity;
	glm::vec3 thrust = thrustRelative * airDensityRelative * params.maxThrust * glm::vec3{0, 0, -1};
	netForce += thrust;
	netTorque += glm::cross(params.thrustPoint, thrust);
}

glm::vec3 AirplaneDynamics::computeAirVelocity(const State& state, const glm::vec3& point)
{
	return -state.velocity - glm::cross(state.angVelocityRad, point);
}
