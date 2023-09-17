#ifndef AIRPLANE_PARAMS_HPP
#define AIRPLANE_PARAMS_HPP

#include "physics/surface_params.hpp"
#include "physics/fuselage_params.hpp"
#include "physics/propulsion_params.hpp"

#include <glm/glm.hpp>

struct AirplaneParams
{
	float mass{};
	glm::mat3 momentOfInertia{};
	glm::vec3 nosePosition{};
	SurfaceParams hStab;
	SurfaceParams vStab;
	SurfaceParams leftWing;
	SurfaceParams rightWing;
	FuselageParams fuselage;
	PropulsionParams propulsion;

	AirplaneParams
	(
		float mass, const glm::mat3& momentOfInertia, const glm::vec3& centerOfMass,

		float hStabArea, float hStabLiftCoefConst, float hStabLiftCoefDeriv,
		float hStabCriticalAngleDeg, const glm::vec3& hStabLiftPoint,
		const glm::vec3& hStabNormalForcePoint, float elevatorArea, float elevatorLiftCoefDeriv,
		float elevatorMinAngleDeg, float elevatorMaxAngleDeg, const glm::vec3& elevatorForcePoint,

		float vStabArea, float vStabLiftCoefConst, float vStabLiftCoefDeriv,
		float vStabCriticalAngleDeg, const glm::vec3& vStabLiftPoint,
		const glm::vec3& vStabNormalForcePoint, float rudderArea, float rudderLiftCoefDeriv,
		float rudderMaxAngleDeg, const glm::vec3& rudderForcePoint,

		float wingsArea, float wingsLiftCoefConst, float wingsLiftCoefDeriv,
		float wingsCriticalAngleDeg, const glm::vec3& rightWingLiftPoint,
		const glm::vec3& rightWingNormalForcePoint, float aileronsArea, float aileronsLiftCoefDeriv,
		float aileronsMaxAngleDeg, const glm::vec3& rightAileronForcePoint,

		float fuselageFrontArea, float fuselageFrontDragCoef,
		const glm::vec3& fuselageFrontDragPoint, float fuselageSideArea,
		float fuselageSideDragCoef, const glm::vec3& fuselageSideDragPoint,

		float maxThrustN
	);
};

#endif
