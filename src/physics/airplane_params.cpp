#include "physics/airplane_params.hpp"

#include "physics/surface_params.hpp"

#include <glm/glm.hpp>

AirplaneParams::AirplaneParams
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
) :
	mass{mass},
	momentOfInertia{momentOfInertia},
	nosePosition{-centerOfMass}
{
	hStab.area = hStabArea;
	hStab.liftCoefConst = hStabLiftCoefConst;
	hStab.liftCoefDeriv = hStabLiftCoefDeriv;
	hStab.criticalAngleRad = glm::radians(hStabCriticalAngleDeg);
	hStab.liftPoint = hStabLiftPoint - centerOfMass;
	hStab.normalForcePoint = hStabNormalForcePoint - centerOfMass;
	hStab.ctrlArea = elevatorArea;
	hStab.ctrlLiftCoefDeriv = elevatorLiftCoefDeriv;
	hStab.ctrlMinAngleRad = elevatorMinAngleDeg;
	hStab.ctrlMaxAngleRad = elevatorMaxAngleDeg;
	hStab.ctrlForcePoint = elevatorForcePoint - centerOfMass;

	vStab.area = vStabArea;
	vStab.liftCoefConst = vStabLiftCoefConst;
	vStab.liftCoefDeriv = vStabLiftCoefDeriv;
	vStab.criticalAngleRad = glm::radians(vStabCriticalAngleDeg);
	vStab.liftPoint = vStabLiftPoint - centerOfMass;
	vStab.normalForcePoint = vStabNormalForcePoint - centerOfMass;
	vStab.ctrlArea = rudderArea;
	vStab.ctrlLiftCoefDeriv = rudderLiftCoefDeriv;
	vStab.ctrlMinAngleRad = -rudderMaxAngleDeg;
	vStab.ctrlMaxAngleRad = rudderMaxAngleDeg;
	vStab.ctrlForcePoint = rudderForcePoint - centerOfMass;

	leftWing.area = wingsArea / 2;
	leftWing.liftCoefConst = wingsLiftCoefConst;
	leftWing.liftCoefDeriv = wingsLiftCoefDeriv;
	leftWing.criticalAngleRad = glm::radians(wingsCriticalAngleDeg);
	leftWing.liftPoint = rightWingLiftPoint - centerOfMass;
	leftWing.liftPoint.x *= -1;
	leftWing.normalForcePoint = rightWingNormalForcePoint - centerOfMass;
	leftWing.normalForcePoint.x *= -1;
	leftWing.ctrlArea = aileronsArea / 2;
	leftWing.ctrlLiftCoefDeriv = aileronsLiftCoefDeriv;
	leftWing.ctrlMinAngleRad = -aileronsMaxAngleDeg;
	leftWing.ctrlMaxAngleRad = aileronsMaxAngleDeg;
	leftWing.ctrlForcePoint = rightAileronForcePoint - centerOfMass;
	leftWing.ctrlForcePoint.x *= -1;

	rightWing.area = wingsArea / 2;
	rightWing.liftCoefConst = wingsLiftCoefConst;
	rightWing.liftCoefDeriv = wingsLiftCoefDeriv;
	rightWing.criticalAngleRad = glm::radians(wingsCriticalAngleDeg);
	rightWing.liftPoint = rightWingLiftPoint - centerOfMass;
	rightWing.normalForcePoint = rightWingNormalForcePoint - centerOfMass;
	rightWing.ctrlArea = aileronsArea / 2;
	rightWing.ctrlLiftCoefDeriv = aileronsLiftCoefDeriv;
	rightWing.ctrlMinAngleRad = -aileronsMaxAngleDeg;
	rightWing.ctrlMaxAngleRad = aileronsMaxAngleDeg;
	rightWing.ctrlForcePoint = rightAileronForcePoint - centerOfMass;

	fuselage.frontArea = fuselageFrontArea;
	fuselage.frontDragCoef = fuselageFrontDragCoef;
	fuselage.frontDragPoint = fuselageFrontDragPoint - centerOfMass;
	fuselage.sideArea = fuselageSideArea;
	fuselage.sideDragCoef = fuselageSideDragCoef;
	fuselage.sideDragPoint = fuselageSideDragPoint - centerOfMass;

	propulsion.maxThrustN = maxThrustN;
}
