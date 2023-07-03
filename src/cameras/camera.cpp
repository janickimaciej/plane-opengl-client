#include "camera.hpp"

Camera::Camera(glm::mat4 projectionMatrix) : projectionMatrix(projectionMatrix) { }

void Camera::updateShaderMatrices(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) const {
	glm::mat4 viewMatrix = getViewMatrix();

	surfaceShaderProgram.use();
	surfaceShaderProgram.setUniformMatrix4f("projectionViewMatrix", projectionMatrix*viewMatrix);
	surfaceShaderProgram.setUniform3f("cameraPosition", getCameraPosition());

	lightShaderProgram.use();
	lightShaderProgram.setUniformMatrix4f("projectionViewMatrix", projectionMatrix*viewMatrix);
	lightShaderProgram.setUniform3f("cameraPosition", getCameraPosition());
}

glm::mat4 Camera::getOriginMatrix() const {
	return glm::mat4(1);
}

glm::mat4 Camera::getCameraMatrix() const {
	return getOriginMatrix()*matrix;
}

glm::vec3 Camera::getCameraPosition() const {
	glm::vec4 cameraPosition = getCameraMatrix()*glm::vec4(0, 0, 0, 1);
	return glm::vec3(cameraPosition);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::inverse(getCameraMatrix());
}

void Camera::use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) {
	updateShaderMatrices(surfaceShaderProgram, lightShaderProgram);
}
