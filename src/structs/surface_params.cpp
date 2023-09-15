#include "structs/surface_params.hpp"

SurfaceParams::SurfaceParams(float area, float length, float coef, float ctrlCoef,
	float ctrlMinAngleDeg, float ctrlMaxAngleDeg) :
	area{area},
	length{length},
	coef{coef},
	ctrlCoef{ctrlCoef},
	ctrlMinAngleDeg{ctrlMinAngleDeg},
	ctrlMaxAngleDeg{ctrlMaxAngleDeg}
{ }
