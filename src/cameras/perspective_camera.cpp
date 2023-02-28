#include "perspective_camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane) :
	Camera(glm::perspective(glm::radians(FoVDeg), aspectRatio, nearPlane, farPlane)), FoVDeg(FoVDeg), nearPlane(nearPlane),
	farPlane(farPlane) { }

void PerspectiveCamera::setAspectRatio(float aspectRatio) {
	projectionMatrix = glm::perspective(glm::radians(FoVDeg), aspectRatio, nearPlane, farPlane);
}
