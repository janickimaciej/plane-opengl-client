#include "mesh_light.hpp"

MeshLight::MeshLight(const ShaderProgram& surfaceShaderProgram, unsigned int id, Mesh& mesh,
	float attenuationQuadratic, float attenuationLinear, float attenuationConstant, glm::vec3 color) :
	Light(surfaceShaderProgram, id, attenuationQuadratic, attenuationLinear, attenuationConstant, color),
	meshInstance(mesh), surfaceShaderProgram(surfaceShaderProgram) { }

void MeshLight::render() const {
	meshInstance.render();
}

void MeshLight::scale(float scaleRatio) {
	meshInstance.scale(scaleRatio);
	updateShaderLightMeshMatrix();
}

void MeshLight::rotate(glm::vec3 axis, float angleDeg) {
	meshInstance.rotate(axis, angleDeg);
	updateShaderLightMeshMatrix();
}

void MeshLight::translate(glm::vec3 translation) {
	meshInstance.translate(translation);
	updateShaderLightMeshMatrix();
}

void MeshLight::pitch(float angleDeg) {
	meshInstance.pitch(angleDeg);
	updateShaderLightMeshMatrix();
}

void MeshLight::yaw(float angleDeg) {
	meshInstance.yaw(angleDeg);
	updateShaderLightMeshMatrix();
}

void MeshLight::roll(float angleDeg) {
	meshInstance.roll(angleDeg);
	updateShaderLightMeshMatrix();
}

void MeshLight::moveAlongZ(float distance) {
	meshInstance.moveAlongZ(distance);
	updateShaderLightMeshMatrix();
}
