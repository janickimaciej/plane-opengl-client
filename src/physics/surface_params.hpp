#ifndef SURFACE_PARAMS_HPP
#define SURFACE_PARAMS_HPP

#include <glm/glm.hpp>

struct SurfaceParams
{
	float area{};
	float liftCoefConst{};
	float liftCoefDeriv{};
	float criticalAngleRad{};
	glm::vec3 liftPoint{};
	glm::vec3 normalForcePoint{};

	float ctrlArea{};
	float ctrlLiftCoefDeriv{};
	float ctrlMinAngleRad{};
	float ctrlMaxAngleRad{};
	glm::vec3 ctrlForcePoint{};
};

#endif
