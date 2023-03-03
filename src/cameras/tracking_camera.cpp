#include "tracking_camera.hpp"
#include <glm/glm.hpp>

void TrackingCamera::aimAtModel() {
	glm::vec3 modelPosition = model.getPosition();
	state.direction = glm::vec4(glm::normalize(state.position - modelPosition), 0);
	state.right = glm::vec4(glm::normalize(glm::cross(glm::vec3(0, 1, 0), glm::vec3(state.direction))), 0);
	state.up = glm::vec4(glm::normalize(glm::cross(glm::vec3(state.direction), glm::vec3(state.right))), 0);
	updateMatrix();
}

TrackingCamera::TrackingCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
	const Model& model) : PerspectiveCamera(FoVDeg, aspectRatio, nearPlane, farPlane), model(model) { }

void TrackingCamera::use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) {
	aimAtModel();
	Camera::use(surfaceShaderProgram, lightShaderProgram);
}
