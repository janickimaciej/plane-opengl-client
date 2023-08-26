#include "airplane_models.hpp"

#include "structs/airplane_parameters.hpp"
#include "structs/control_surfaces_constraints.hpp"
#include "structs/surface_parameters.hpp"

#include <glm/glm.hpp>

constexpr float mustangMass = 4000;
constexpr glm::mat3 mustangMomentOfInertia
{
	17400, 0, 0,
	0, 29500, 350,
	0, 350, 14800
};

const SurfaceParameters mustangWings{21.41f, 11, 3.82f, 1};
const SurfaceParameters mustangHStab{3.54f, 3.85f, 3.82f, 1};
const SurfaceParameters mustangVStab{1.23f, 1.11f, 3.82f, 1};
const ControlSurfacesConstraints mustangConstraints{-20, 20, 15, 15};
const AirplaneParameters mustang{mustangMass, mustangMomentOfInertia, mustangWings, mustangHStab,
	mustangVStab, mustangConstraints};

constexpr float giroscopeMass = 1;
constexpr glm::mat3 giroscopeMomentOfInertia
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};
const SurfaceParameters giroscopeWings{1, 1, 1, 1};
const ControlSurfacesConstraints giroscopeConstraints{1, 1, 1, 1};
const AirplaneParameters giroscope{giroscopeMass, giroscopeMomentOfInertia, giroscopeWings,
	giroscopeWings, giroscopeWings, giroscopeConstraints};
