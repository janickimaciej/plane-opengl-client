#include "mesh_light.hpp"

MeshLight::MeshLight(const ShaderProgram& surfaceShaderProgram, unsigned int id, const Mesh& mesh,
	float attenuationQuadratic, float attenuationLinear, float attenuationConstant, glm::vec3 color) :
	Light(surfaceShaderProgram, id, attenuationQuadratic, attenuationLinear, attenuationConstant, color),
	meshInstance(mesh), surfaceShaderProgram(surfaceShaderProgram) { }

void MeshLight::render(glm::mat4 modelMatrix) const {
	meshInstance.render(modelMatrix);
}

void MeshLight::scale(float scaleRatio, glm::mat4 modelMatrix) {
	meshInstance.scale(scaleRatio);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::rotate(glm::vec3 axis, float angleDeg, glm::mat4 modelMatrix) {
	meshInstance.rotate(axis, angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::translate(glm::vec3 translation, glm::mat4 modelMatrix) {
	meshInstance.translate(translation);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::pitch(float angleDeg, glm::mat4 modelMatrix) {
	meshInstance.pitch(angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::yaw(float angleDeg, glm::mat4 modelMatrix) {
	meshInstance.yaw(angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::roll(float angleDeg, glm::mat4 modelMatrix) {
	meshInstance.roll(angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::moveAlongZ(float distance, glm::mat4 modelMatrix) {
	meshInstance.moveAlongZ(distance);
	updateShaderLightTranslation(modelMatrix);
}
