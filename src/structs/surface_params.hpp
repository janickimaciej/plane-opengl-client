#ifndef SURFACE_PARAMS_HPP
#define SURFACE_PARAMS_HPP

struct SurfaceParams
{
	float area{};
	float length{};
	float coef{};
	float ctrlCoef{};
	float ctrlMinAngleDeg{};
	float ctrlMaxAngleDeg{};

	SurfaceParams(float area, float length, float coef, float ctrlCoef, float ctrlMinAngleDeg,
		float ctrlMaxAngleDeg);
};

#endif
