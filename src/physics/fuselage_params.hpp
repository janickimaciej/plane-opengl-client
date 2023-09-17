#ifndef FUSELAGE_PARAMS_HPP
#define FUSELAGE_PARAMS_HPP

#include <glm/glm.hpp>

struct FuselageParams
{
	float frontArea{};
	float frontDragCoef{};
	glm::vec3 frontDragPoint{};

	float sideArea{};
	float sideDragCoef{};
	glm::vec3 sideDragPoint{};
};

#endif
