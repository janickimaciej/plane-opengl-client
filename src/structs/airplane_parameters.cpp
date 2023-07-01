#include "airplane_parameters.hpp"

AirplaneParameters::AirplaneParameters(SurfaceParameters wingsParameters,
	SurfaceParameters hStabParameters, SurfaceParameters vStabParameters,
	ControlSurfacesConstraints controlSurfacesConstraints) :
	wingsParameters(wingsParameters), hStabParameters(hStabParameters),
	vStabParameters(vStabParameters),
	controlSurfacesConstraints(controlSurfacesConstraints) { }
