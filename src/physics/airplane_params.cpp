#include "physics/airplane_params.hpp"

#include "physics/surface_params.hpp"

#include <glm/glm.hpp>

AirplaneParams::AirplaneParams(float mass, const glm::mat3& momentOfInertia,
	const SurfaceParams& wingsParams, const SurfaceParams& hStabParams,
	const SurfaceParams& vStabParams) :
	mass{mass},
	momentOfInertia{momentOfInertia},
	wings{wingsParams},
	hStab{hStabParams},
	vStab{vStabParams}
{ }
