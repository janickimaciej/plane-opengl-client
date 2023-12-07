#pragma once

#include "common/airplane_database.hpp"
#include "common/airplane_type_name.hpp"
#include "physics/airplane_params/airplane_params.hpp"

#include <glm/glm.hpp>

#include <cstddef>

namespace Physics
{
	namespace
	{
		inline constexpr float mass = 4000;
		inline constexpr glm::mat3 momentOfInertia
		{
			17400, 0, 0,
			0, 29500, 350,
			0, 350, 14800
		};
		inline constexpr glm::vec3 centerOfMass = Common::airplaneCenterOfMassDatabase[
			static_cast<std::size_t>(Common::AirplaneTypeName::mustang)];
	
		inline constexpr float hStabIncidenceAngleDeg = 0;
		inline constexpr float hStabArea = 3.54f;
		inline constexpr float hStabLiftCoefConst = 0;
		inline constexpr float hStabLiftCoefDeriv = 3.82f;
		inline constexpr float hStabNormalForceCoef = 2;
		inline constexpr float hStabCriticalAngleNegativeDeg = -18;
		inline constexpr float hStabCriticalAnglePositiveDeg = 18;
		inline constexpr glm::vec3 hStabLiftPoint{0, 0.32, 8.34};
		inline constexpr glm::vec3 hStabNormalForcePoint{0, 0.32, 8.62};
		inline constexpr float elevatorArea = 3.54f; // area of the part of the hStab with elevator
		inline constexpr float elevatorLiftCoefDeriv = 0.02f;
		inline constexpr float elevatorMinAngleDeg = -20;
		inline constexpr float elevatorMaxAngleDeg = 20;
		inline constexpr glm::vec3 elevatorForcePoint{0, 0.32, 8.62};
	
		inline constexpr float vStabIncidenceAngleDeg = 0;
		inline constexpr float vStabArea = 1.87f;
		inline constexpr float vStabLiftCoefConst = 0;
		inline constexpr float vStabLiftCoefDeriv = 3.82f;
		inline constexpr float vStabNormalForceCoef = 2;
		inline constexpr float vStabCriticalAngleNegativeDeg = -18;
		inline constexpr float vStabCriticalAnglePositiveDeg = 18;
		inline constexpr glm::vec3 vStabLiftPoint{0, 0.87, 8.7};
		inline constexpr glm::vec3 vStabNormalForcePoint{0, 0.87, 9.01};
		inline constexpr float rudderArea = 1.87f; // area of the part of the vStab with rudder
		inline constexpr float rudderLiftCoefDeriv = 0.02f;
		inline constexpr float rudderMaxAngleDeg = 15;
		inline constexpr glm::vec3 rudderForcePoint{0, 0.79, 9.13};
	
		inline constexpr float wingsIncidenceAngleDeg = 0;
		inline constexpr float wingsArea = 21.42f;
		inline constexpr float wingsLiftCoefConst = 0;
		inline constexpr float wingsLiftCoefDeriv = 3.82f;
		inline constexpr float wingsNormalForceCoef = 2;
		inline constexpr float wingsCriticalAngleNegativeDeg = -18;
		inline constexpr float wingsCriticalAnglePositiveDeg = 18;
		inline constexpr glm::vec3 rightWingLiftPoint{2.62, -0.56, 3.45};
		inline constexpr glm::vec3 rightWingNormalForcePoint{2.62, -0.56, 3.93};
		inline constexpr float aileronsArea = 5.9f; // area of the part of the wings with ailerons
		inline constexpr float aileronsLiftCoefDeriv = 0.02f;
		inline constexpr float aileronsMaxAngleDeg = 15;
		inline constexpr glm::vec3 rightAileronForcePoint{4.25, -0.56, 3.77};

		inline constexpr float fuselageFrontArea = 1.53f;
		inline constexpr float fuselageFrontDragCoef = 0.35f;
		inline constexpr glm::vec3 fuselageFrontDragPoint{0, 0, 0};
		inline constexpr float fuselageSideArea = 8.67f;
		inline constexpr float fuselageSideDragCoef = 0.59f;
		inline constexpr glm::vec3 fuselageSideDragPoint{0, 0, 4.61};

		inline constexpr float maxThrust = 5500;
		inline constexpr glm::vec3 thrustPoint{0, 0, 0.44};
	};

	inline const AirplaneParams mustangParams
	{
		mass, momentOfInertia, centerOfMass,

		hStabIncidenceAngleDeg, hStabArea, hStabLiftCoefConst, hStabLiftCoefDeriv,
		hStabNormalForceCoef, hStabCriticalAngleNegativeDeg, hStabCriticalAnglePositiveDeg,
		hStabLiftPoint, hStabNormalForcePoint, elevatorArea, elevatorLiftCoefDeriv,
		elevatorMinAngleDeg, elevatorMaxAngleDeg, elevatorForcePoint,

		vStabIncidenceAngleDeg, vStabArea, vStabLiftCoefConst, vStabLiftCoefDeriv,
		vStabNormalForceCoef, vStabCriticalAngleNegativeDeg, vStabCriticalAnglePositiveDeg,
		vStabLiftPoint, vStabNormalForcePoint, rudderArea, rudderLiftCoefDeriv, rudderMaxAngleDeg,
		rudderForcePoint,

		wingsIncidenceAngleDeg, wingsArea, wingsLiftCoefConst, wingsLiftCoefDeriv,
		wingsNormalForceCoef, wingsCriticalAngleNegativeDeg, wingsCriticalAnglePositiveDeg,
		rightWingLiftPoint, rightWingNormalForcePoint, aileronsArea, aileronsLiftCoefDeriv,
		aileronsMaxAngleDeg, rightAileronForcePoint,

		fuselageFrontArea, fuselageFrontDragCoef, fuselageFrontDragPoint, fuselageSideArea,
		fuselageSideDragCoef, fuselageSideDragPoint,

		maxThrust, thrustPoint
	};
};
