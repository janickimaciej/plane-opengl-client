#ifndef SURFACE_PARAMETERS
#define SURFACE_PARAMETERS

struct SurfaceParameters {
	float area;
	float span;
	float coef;
	float controlCoef;

	SurfaceParameters(float area, float span, float coef, float controlCoef);
};

#endif
