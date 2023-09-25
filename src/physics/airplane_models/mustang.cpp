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
	constexpr glm::vec3 centerOfMass{0, 0, 4.05f};
	
	constexpr float hStabIncidenceAngleDeg = 0;
	constexpr float hStabArea = 3.54f;
	constexpr float hStabLiftCoefConst = 0;
	constexpr float hStabLiftCoefDeriv = 3.82f;
	constexpr float hStabNormalForceCoef = 2;
	constexpr float hStabCriticalAngleNegativeDeg = -18;
	constexpr float hStabCriticalAnglePositiveDeg = 18;
	constexpr glm::vec3 hStabLiftPoint{0, 0.32, 8.34};
	constexpr glm::vec3 hStabNormalForcePoint{0, 0.32, 8.62};
	constexpr float elevatorArea = 3.54f; // area of the part of the hStab with elevator
	constexpr float elevatorLiftCoefDeriv = 0.02f;
	constexpr float elevatorMinAngleDeg = -20;
	constexpr float elevatorMaxAngleDeg = 20;
	constexpr glm::vec3 elevatorForcePoint{0, 0.32, 8.62};
	
	constexpr float vStabIncidenceAngleDeg = 0;
	constexpr float vStabArea = 1.87f;
	constexpr float vStabLiftCoefConst = 0;
	constexpr float vStabLiftCoefDeriv = 3.82f;
	constexpr float vStabNormalForceCoef = 2;
	constexpr float vStabCriticalAngleNegativeDeg = -18;
	constexpr float vStabCriticalAnglePositiveDeg = 18;
	constexpr glm::vec3 vStabLiftPoint{0, 0.87, 8.7};
	constexpr glm::vec3 vStabNormalForcePoint{0, 0.87, 9.01};
	constexpr float rudderArea = 1.87f; // area of the part of the vStab with rudder
	constexpr float rudderLiftCoefDeriv = 0.02f;
	constexpr float rudderMaxAngleDeg = 15;
	constexpr glm::vec3 rudderForcePoint{0, 0.79, 9.13};
	
	constexpr float wingsIncidenceAngleDeg = 0;
	constexpr float wingsArea = 21.42f;
	constexpr float wingsLiftCoefConst = 0;
	constexpr float wingsLiftCoefDeriv = 3.82f;
	constexpr float wingsNormalForceCoef = 2;
	constexpr float wingsCriticalAngleNegativeDeg = -18;
	constexpr float wingsCriticalAnglePositiveDeg = 18;
	constexpr glm::vec3 rightWingLiftPoint{2.62, -0.56, 3.45};
	constexpr glm::vec3 rightWingNormalForcePoint{2.62, -0.56, 3.93};
	constexpr float aileronsArea = 5.9f; // area of the part of the wings with ailerons
	constexpr float aileronsLiftCoefDeriv = 0.02f;
	constexpr float aileronsMaxAngleDeg = 15;
	constexpr glm::vec3 rightAileronForcePoint{4.25, -0.56, 3.77};

	constexpr float fuselageFrontArea = 1.53f;
	constexpr float fuselageFrontDragCoef = 0.35f;
	constexpr glm::vec3 fuselageFrontDragPoint{0, 0, 0};
	constexpr float fuselageSideArea = 8.67f;
	constexpr float fuselageSideDragCoef = 0.59f;
	constexpr glm::vec3 fuselageSideDragPoint{0, 0, 4.61};

	constexpr float maxThrust = 5500;
	constexpr glm::vec3 thrustPoint{0, 0, 0.44};
}

const AirplaneParams mustang
{
	mass, momentOfInertia, centerOfMass,

	hStabIncidenceAngleDeg, hStabArea, hStabLiftCoefConst, hStabLiftCoefDeriv, hStabNormalForceCoef,
	hStabCriticalAngleNegativeDeg, hStabCriticalAnglePositiveDeg, hStabLiftPoint,
	hStabNormalForcePoint, elevatorArea, elevatorLiftCoefDeriv, elevatorMinAngleDeg,
	elevatorMaxAngleDeg, elevatorForcePoint,

	vStabIncidenceAngleDeg, vStabArea, vStabLiftCoefConst, vStabLiftCoefDeriv, vStabNormalForceCoef,
	vStabCriticalAngleNegativeDeg, vStabCriticalAnglePositiveDeg, vStabLiftPoint,
	vStabNormalForcePoint, rudderArea, rudderLiftCoefDeriv, rudderMaxAngleDeg, rudderForcePoint,

	wingsIncidenceAngleDeg, wingsArea, wingsLiftCoefConst, wingsLiftCoefDeriv, wingsNormalForceCoef,
	wingsCriticalAngleNegativeDeg, wingsCriticalAnglePositiveDeg, rightWingLiftPoint,
	rightWingNormalForcePoint, aileronsArea, aileronsLiftCoefDeriv, aileronsMaxAngleDeg,
	rightAileronForcePoint,

	fuselageFrontArea, fuselageFrontDragCoef, fuselageFrontDragPoint, fuselageSideArea,
	fuselageSideDragCoef, fuselageSideDragPoint,

	maxThrust, thrustPoint
};
