#include "physics/airplane_models.hpp"

#include "physics/airplane_params.hpp"
#include "physics/surface_params.hpp"

#include <glm/glm.hpp>

namespace
{
	constexpr float mass = 4000;
	constexpr glm::mat3 momentOfInertia
	{
		17400, 0, 0,
		0, 29500, 350,
		0, 350, 14800
	};
	constexpr glm::vec3 centerOfMass{0, 0, 4};
	
	constexpr float hStabArea = 3.54f;
	constexpr float hStabLiftCoefConst = 0;
	constexpr float hStabLiftCoefDeriv = 3.82f;
	constexpr float hStabCriticalAngleDeg = 18;
	constexpr glm::vec3 hStabLiftPoint{0, 0.32, 8.34};
	constexpr glm::vec3 hStabNormalForcePoint{0, 0.32, 8.62};
	constexpr float elevatorArea = 3.54f; // area of the part of the hStab with elevator
	constexpr float elevatorLiftCoefDeriv = 1; //tmp value
	constexpr float elevatorMinAngleDeg = -20;
	constexpr float elevatorMaxAngleDeg = 20;
	constexpr glm::vec3 elevatorForcePoint{0, 0.32, 8.62};
	
	constexpr float vStabArea = 1.87f;
	constexpr float vStabLiftCoefConst = 0;
	constexpr float vStabLiftCoefDeriv = 3.82f;
	constexpr float vStabCriticalAngleDeg = 18;
	constexpr glm::vec3 vStabLiftPoint{0, 0.87, 8.7};
	constexpr glm::vec3 vStabNormalForcePoint{0, 0.87, 9.01};
	constexpr float rudderArea = 1.87f; // area of the part of the vStab with rudder
	constexpr float rudderLiftCoefDeriv = 1; //tmp value
	constexpr float rudderMaxAngleDeg = 15;
	constexpr glm::vec3 rudderForcePoint{0, 0.79, 9.13};

	constexpr float wingsArea = 21.42f;
	constexpr float wingsLiftCoefConst = 0;
	constexpr float wingsLiftCoefDeriv = 3.82f;
	constexpr float wingsCriticalAngleDeg = 18;
	constexpr glm::vec3 rightWingLiftPoint{2.62, -0.56, 3.45};
	constexpr glm::vec3 rightWingNormalForcePoint{2.62, -0.56, 3.93};
	constexpr float aileronsArea = 5.9f; // area of the part of the wings with ailerons
	constexpr float aileronsLiftCoefDeriv = 1; //tmp value
	constexpr float aileronsMaxAngleDeg = 15;
	constexpr glm::vec3 rightAileronForcePoint{4.25, -0.56, 3.77};

	constexpr float fuselageFrontArea = 1.53f;
	constexpr float fuselageFrontDragCoef = 0.35f;
	constexpr glm::vec3 fuselageFrontDragPoint{0, 0, 0};
	constexpr float fuselageSideArea = 8.67f;
	constexpr float fuselageSideDragCoef = 0.59f;
	constexpr glm::vec3 fuselageSideDragPoint{0, 0, 4.61};

	constexpr float maxThrustN = 5500;
}

const AirplaneParams mustang
{
	mass, momentOfInertia, centerOfMass,

	hStabArea, hStabLiftCoefConst, hStabLiftCoefDeriv, hStabCriticalAngleDeg, hStabLiftPoint,
	hStabNormalForcePoint, elevatorArea, elevatorLiftCoefDeriv, elevatorMinAngleDeg,
	elevatorMaxAngleDeg, elevatorForcePoint,

	vStabArea, vStabLiftCoefConst, vStabLiftCoefDeriv, vStabCriticalAngleDeg, vStabLiftPoint,
	vStabNormalForcePoint, rudderArea, rudderLiftCoefDeriv, rudderMaxAngleDeg, rudderForcePoint,

	wingsArea, wingsLiftCoefConst, wingsLiftCoefDeriv, wingsCriticalAngleDeg, rightWingLiftPoint,
	rightWingNormalForcePoint, aileronsArea, aileronsLiftCoefDeriv, aileronsMaxAngleDeg,
	rightAileronForcePoint,

	fuselageFrontArea, fuselageFrontDragCoef, fuselageFrontDragPoint, fuselageSideArea,
	fuselageSideDragCoef, fuselageSideDragPoint,

	maxThrustN
};
