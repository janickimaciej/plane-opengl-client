#include "structs/airplane_parameters.hpp"

#include "structs/control_surfaces_constraints.hpp"
#include "structs/surface_parameters.hpp"

#include <glm/glm.hpp>

AirplaneParameters::AirplaneParameters(float mass, const glm::mat3& momentOfInertia,
	const SurfaceParameters& wingsParameters, const SurfaceParameters& hStabParameters,
	const SurfaceParameters& vStabParameters,
	const ControlSurfacesConstraints& controlSurfacesConstraints) :
	mass{mass},
	momentOfInertia{momentOfInertia},
	wingsParameters{wingsParameters},
	hStabParameters{hStabParameters},
	vStabParameters{vStabParameters},
	controlSurfacesConstraints{controlSurfacesConstraints}
{ }
