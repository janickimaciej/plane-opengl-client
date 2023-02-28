#include "spot_light.hpp"
#include <glad/glad.h>

unsigned int SpotLight::idCounter = 0;

void SpotLight::updateShaderLightValues() const {
	glUseProgram(surfaceShaderProgram.id);
	std::string commonString = "spotLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniform1f(commonString + "cutoffInnerRad", glm::radians(cutoffInnerDeg));
	surfaceShaderProgram.setUniform1f(commonString + "cutoffOuterRad", glm::radians(cutoffOuterDeg));
	surfaceShaderProgram.setUniform3f(commonString + "color", color);
	surfaceShaderProgram.setUniform1f(commonString + "attenuationQuadratic", attenuationQuadratic);
	surfaceShaderProgram.setUniform1f(commonString + "attenuationLinear", attenuationLinear);
	surfaceShaderProgram.setUniform1f(commonString + "attenuationConstant", attenuationConstant);
}

void SpotLight::updateShaderLightMeshMatrix() const {
	glUseProgram(surfaceShaderProgram.id);
	std::string commonString = "spotLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniformMatrix4f(commonString + "meshMatrix", meshInstance.getMatrix());
}

SpotLight::SpotLight(const ShaderProgram& surfaceShaderProgram, Mesh& mesh, float attenuationQuadratic,
	float attenuationLinear, float attenuationConstant, glm::vec3 color, float cutoffInnerDeg,
	float cutoffOuterDeg) :	MeshLight(surfaceShaderProgram, idCounter++, mesh, attenuationQuadratic,
	attenuationLinear, attenuationConstant, color), cutoffInnerDeg(cutoffInnerDeg),
	cutoffOuterDeg(cutoffOuterDeg) {
	updateShaderLightValues();
	updateShaderLightMeshMatrix();
}

void SpotLight::updateShaderLightModelMatrix(glm::mat4 modelMatrix) const {
	glUseProgram(surfaceShaderProgram.id);
	std::string commonString = "spotLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniformMatrix4f(commonString + "modelMatrix", modelMatrix);
}
