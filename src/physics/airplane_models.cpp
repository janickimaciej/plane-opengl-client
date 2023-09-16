#include "physics/airplane_models.hpp"

#include "physics/airplane_params.hpp"
#include "physics/surface_params.hpp"

#include <glm/glm.hpp>

// MUSTANG
constexpr float mustangMass = 4000;
constexpr glm::mat3 mustangMomentOfInertia
{
	17400, 0, 0,
	0, 29500, 350,
	0, 350, 14800
};

const SurfaceParams mustangWings{21.41f, 11, 3.82f, 1, -15, 15};
const SurfaceParams mustangHStab{3.54f, 3.85f, 3.82f, 1, -20, 20};
const SurfaceParams mustangVStab{1.23f, 1.11f, 3.82f, 1, 15, 15};
const AirplaneParams mustang{mustangMass, mustangMomentOfInertia, mustangWings, mustangHStab,
	mustangVStab};

// GIROSCOPE
constexpr float giroscopeMass = 1;
constexpr glm::mat3 giroscopeMomentOfInertia
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};
const SurfaceParams giroscopeWings{1, 1, 1, 1, 1, 1};
const AirplaneParams giroscope{giroscopeMass, giroscopeMomentOfInertia, giroscopeWings,
	giroscopeWings, giroscopeWings};
