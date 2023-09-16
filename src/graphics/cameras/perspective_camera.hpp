#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "graphics/cameras/camera.hpp"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane);
	void setAspectRatio(float aspectRatio);
	virtual ~PerspectiveCamera() = default;

private:
	float m_FoVDeg{};
	float m_nearPlane{};
	float m_farPlane{};
};

#endif
