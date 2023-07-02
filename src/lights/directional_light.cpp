#include "directional_light.hpp"
#include <glad/glad.h>

unsigned int DirectionalLight::idCounter = 0;

void DirectionalLight::updateShaderLightValues() const {
	surfaceShaderProgram.use();
	std::string commonString = "directionalLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniform3f(commonString + "color", color);
	surfaceShaderProgram.setUniform1f(commonString + "attenuationQuadratic", attenuationQuadratic);
	surfaceShaderProgram.setUniform1f(commonString + "attenuationLinear", attenuationLinear);
	surfaceShaderProgram.setUniform1f(commonString + "attenuationConstant", attenuationConstant);
}

DirectionalLight::DirectionalLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
	float attenuationLinear, float attenuationConstant, glm::vec3 color) :
	Light(surfaceShaderProgram, idCounter++, attenuationQuadratic,
	attenuationLinear, attenuationConstant, color) {
	updateShaderLightValues();
}

void DirectionalLight::updateShaderLightModelMatrix(glm::mat4 modelMatrix) const {
	surfaceShaderProgram.use();
	std::string commonString = "directionalLights[" + std::to_string(id) + "].";
	surfaceShaderProgram.setUniformMatrix4f(commonString + "modelMatrix", modelMatrix);
}
