#include "directional_light.hpp"
#include <glad/glad.h>

unsigned int DirectionalLight::idCounter = 0;

void DirectionalLight::updateShaderLightParameters() const {
	surfaceShaderProgram.use();
	std::string prefix = "directionalLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniform3f(prefix + "color", color);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic", attenuationQuadratic);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", attenuationLinear);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", attenuationConstant);
}

DirectionalLight::DirectionalLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
	float attenuationLinear, float attenuationConstant, glm::vec3 color) :
	Light(surfaceShaderProgram, idCounter++, attenuationQuadratic,
	attenuationLinear, attenuationConstant, color) {
	updateShaderLightParameters();
}

void DirectionalLight::updateShaderLightTranslation(glm::mat4 modelMatrix) const {
	surfaceShaderProgram.use();
	std::string prefix = "directionalLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniform3f(prefix + "lightDirection",
		glm::normalize(glm::vec3(modelMatrix*glm::vec4(0, 0, 1, 0))));
}
