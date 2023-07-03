#include "model.hpp"

Model::Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	surfaceShaderProgram(surfaceShaderProgram), lightShaderProgram(lightShaderProgram) { }

void Model::render() const {
	surfaceShaderProgram.use();
	renderSurfaces();

	lightShaderProgram.use();
	renderLights();
}

glm::mat4 Model::getModelMatrix() const {
	return matrix;
}

glm::vec3 Model::getPosition() const {
	return state.position;
}

void Model::scale(float scaleRatio) {
	Movable::scale(scaleRatio);
	updateShaderLightMatrix();
}

void Model::rotate(glm::vec3 axis, float angleDeg) {
	Movable::rotate(axis, angleDeg);
	updateShaderLightMatrix();
}

void Model::resetRotation() {
	Movable::resetRotation();
	updateShaderLightMatrix();
}

void Model::translate(glm::vec3 translation) {
	Movable::translate(translation);
	updateShaderLightMatrix();
}

void Model::pitch(float angleDeg) {
	Movable::pitch(angleDeg);
	updateShaderLightMatrix();
}

void Model::yaw(float angleDeg) {
	Movable::yaw(angleDeg);
	updateShaderLightMatrix();
}

void Model::roll(float angleDeg) {
	Movable::roll(angleDeg);
	updateShaderLightMatrix();
}

void Model::moveAlongZ(float distance) {
	Movable::moveAlongZ(distance);
	updateShaderLightMatrix();
}
