#include "tracking_camera.hpp"
#include <glm/glm.hpp>

void TrackingCamera::aimAtModel() {
	glm::vec3 modelPosition = model.getPosition();
	state.direction = glm::normalize(state.position - modelPosition);
	state.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), glm::vec3(state.direction)));
	state.up = glm::normalize(glm::cross(glm::vec3(state.direction), glm::vec3(state.right)));
	updateMatrix();
}

TrackingCamera::TrackingCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
	const Model& model) : PerspectiveCamera(FoVDeg, aspectRatio, nearPlane, farPlane), model(model) { }

void TrackingCamera::use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) {
	aimAtModel();
	Camera::use(surfaceShaderProgram, lightShaderProgram);
}
