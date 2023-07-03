#include "spot_light.hpp"
#include <glad/glad.h>

unsigned int SpotLight::idCounter = 0;

void SpotLight::updateShaderLightParameters() const {
	surfaceShaderProgram.use();
	std::string prefix = "spotLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniform1f(prefix + "cutoffInnerRad", glm::radians(cutoffInnerDeg));
	surfaceShaderProgram.setUniform1f(prefix + "cutoffOuterRad", glm::radians(cutoffOuterDeg));
	surfaceShaderProgram.setUniform3f(prefix + "color", color);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic", attenuationQuadratic);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", attenuationLinear);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", attenuationConstant);
}

SpotLight::SpotLight(const ShaderProgram& surfaceShaderProgram, const Mesh& mesh, float attenuationQuadratic,
	float attenuationLinear, float attenuationConstant, glm::vec3 color, float cutoffInnerDeg,
	float cutoffOuterDeg, glm::mat4 modelMatrix) :	MeshLight(surfaceShaderProgram, idCounter++, mesh,
	attenuationQuadratic, attenuationLinear, attenuationConstant, color), cutoffInnerDeg(cutoffInnerDeg),
	cutoffOuterDeg(cutoffOuterDeg) {
	updateShaderLightParameters();
	updateShaderLightTranslation(modelMatrix);
}

void SpotLight::updateShaderLightTranslation(glm::mat4 modelMatrix) const {
	surfaceShaderProgram.use();
	std::string prefix = "spotLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniform3f(prefix + "lightDirection",
		glm::normalize(glm::vec3(modelMatrix*meshInstance.getMatrix()*glm::vec4(0, 0, 1, 0))));
	surfaceShaderProgram.setUniform3f(prefix + "lightPosition",
		glm::vec3(modelMatrix*meshInstance.getMatrix()*glm::vec4(0, 0, 0, 1)));
}
