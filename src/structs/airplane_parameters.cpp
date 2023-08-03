#include "structs/airplane_parameters.hpp"

#include "structs/control_surfaces_constraints.hpp"
#include "structs/surface_parameters.hpp"

#include <glm/glm.hpp>

AirplaneParameters::AirplaneParameters(float mass, glm::mat3 momentOfInertia,
	SurfaceParameters wingsParameters, SurfaceParameters hStabParameters,
	SurfaceParameters vStabParameters, ControlSurfacesConstraints controlSurfacesConstraints) :
	mass { mass },
	momentOfInertia { momentOfInertia },
	wingsParameters { wingsParameters },
	hStabParameters { hStabParameters },
	vStabParameters { vStabParameters },
	controlSurfacesConstraints { controlSurfacesConstraints }
{ }
