#ifndef AIRPLANE_PARAMETERS
#define AIRPLANE_PARAMETERS

#include "surface_parameters.hpp"
#include "control_surfaces_constraints.hpp"

struct AirplaneParameters {
	SurfaceParameters wingsParameters;
	SurfaceParameters hStabParameters;
	SurfaceParameters vStabParameters;
	ControlSurfacesConstraints controlSurfacesConstraints;

	AirplaneParameters(SurfaceParameters wingsParameters, SurfaceParameters hStabParameters,
		SurfaceParameters vStabParameters, ControlSurfacesConstraints controlSurfacesConstraints);
};

#endif
