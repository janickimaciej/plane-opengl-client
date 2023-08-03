#ifndef SURFACE_PARAMETERS_HPP
#define SURFACE_PARAMETERS_HPP

struct SurfaceParameters
{
	float area {};
	float span {};
	float coef {};
	float controlCoef {};

	SurfaceParameters(float area, float span, float coef, float controlCoef);
};

#endif
