#include "graphics/cameras/perspective_camera.hpp"

#include "graphics/cameras/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(float FoVDeg, float aspectRatio, float nearPlane,
	float farPlane) :
	Camera{glm::perspective(glm::radians(FoVDeg), aspectRatio, nearPlane, farPlane)},
	m_FoVDeg{FoVDeg},
	m_nearPlane{nearPlane},
	m_farPlane{farPlane}
{ }

void PerspectiveCamera::setAspectRatio(float aspectRatio)
{
	m_projectionMatrix = glm::perspective(glm::radians(m_FoVDeg), aspectRatio, m_nearPlane,
		m_farPlane);
}
