#ifndef AIRPLANE_PARAMETERS_HPP
#define AIRPLANE_PARAMETERS_HPP

#include "structs/control_surfaces_constraints.hpp"
#include "structs/surface_parameters.hpp"

#include <glm/glm.hpp>

struct AirplaneParameters
{
	float mass {};
	glm::mat3 momentOfInertia {};
	SurfaceParameters wingsParameters;
	SurfaceParameters hStabParameters;
	SurfaceParameters vStabParameters;
	ControlSurfacesConstraints controlSurfacesConstraints;

	AirplaneParameters(float mass, glm::mat3 momentOfInertia, SurfaceParameters wingsParameters,
		SurfaceParameters hStabParameters, SurfaceParameters vStabParameters,
		ControlSurfacesConstraints controlSurfacesConstraints);
};

#endif
