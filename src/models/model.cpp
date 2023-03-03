#include "model.hpp"

void Model::updateShaderValues() const {
	surfaceShaderProgram.use();
	surfaceShaderProgram.setUniformMatrix4f("modelMatrix", matrix);
	
	lightShaderProgram.use();
	lightShaderProgram.setUniformMatrix4f("modelMatrix", matrix);
}

Model::Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	surfaceShaderProgram(surfaceShaderProgram), lightShaderProgram(lightShaderProgram) { }

void Model::render() const {
	updateShaderValues();
	
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
	updateShaderLightModelMatrix();
}

void Model::rotate(glm::vec3 axis, float angleDeg) {
	Movable::rotate(axis, angleDeg);
	updateShaderLightModelMatrix();
}

void Model::translate(glm::vec3 translation) {
	Movable::translate(translation);
	updateShaderLightModelMatrix();
}

void Model::pitch(float angleDeg) {
	Movable::pitch(angleDeg);
	updateShaderLightModelMatrix();
}

void Model::yaw(float angleDeg) {
	Movable::yaw(angleDeg);
	updateShaderLightModelMatrix();
}

void Model::roll(float angleDeg) {
	Movable::roll(angleDeg);
	updateShaderLightModelMatrix();
}

void Model::moveAlongZ(float distance) {
	Movable::moveAlongZ(distance);
	updateShaderLightModelMatrix();
}
