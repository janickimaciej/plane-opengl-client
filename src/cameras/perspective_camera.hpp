#ifndef PERSPECTIVE_CAMERA
#define PERSPECTIVE_CAMERA

#include "camera.hpp"

class PerspectiveCamera : public Camera {
	float FoVDeg;
	float nearPlane;
	float farPlane;
public:
	PerspectiveCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane);
	void setAspectRatio(float aspectRatio);

	virtual ~PerspectiveCamera() { }
};

#endif
