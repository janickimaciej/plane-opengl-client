#ifndef SURFACE_PARAMS_HPP
#define SURFACE_PARAMS_HPP

#include <glm/glm.hpp>

struct SurfaceParams
{
	glm::mat3 orientation{};
	glm::mat3 orientationInverse{};

	float area{};
	float liftCoefConst{};
	float liftCoefDeriv{};
	float normalForceCoef{};
	float criticalAngleNegativeRad{};
	float criticalAnglePositiveRad{};
	glm::vec3 liftPoint{};
	glm::vec3 normalForcePoint{};

	float ctrlArea{};
	float ctrlLiftCoefDeriv{};
	float ctrlMinAngleRad{};
	float ctrlMaxAngleRad{};
	glm::vec3 ctrlLiftPoint{};
};

#endif
