#ifndef AIRPLANE_PARAMS_HPP
#define AIRPLANE_PARAMS_HPP

#include "structs/surface_params.hpp"

#include <glm/glm.hpp>

struct AirplaneParams
{
	float mass{};
	glm::mat3 momentOfInertia{};
	SurfaceParams wings;
	SurfaceParams hStab;
	SurfaceParams vStab;

	AirplaneParams(float mass, const glm::mat3& momentOfInertia,
		const SurfaceParams& wingsParams, const SurfaceParams& hStabParams,
		const SurfaceParams& vStabParams);
};

#endif
