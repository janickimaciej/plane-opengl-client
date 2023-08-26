#include "lights/directional_light.hpp"

#include "lights/light.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

#include <string>

DirectionalLight::DirectionalLight(const ShaderProgram& surfaceShaderProgram,
	float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
	const glm::vec3& color) :
	Light{surfaceShaderProgram, s_idCounter, attenuationQuadratic, attenuationLinear,
		attenuationConstant, color}
{
	++s_idCounter;
	updateShaderLightParameters();
}

void DirectionalLight::updateShaderLightTranslation(const glm::mat4& modelMatrix) const
{
	surfaceShaderProgram.use();
	const std::string prefix = "directionalLights[" + std::to_string(m_id) + "].";
	surfaceShaderProgram.setUniform3f(prefix + "lightDirection",
		glm::normalize(glm::vec3{modelMatrix * glm::vec4{0, 0, 1, 0}}));
}

void DirectionalLight::updateShaderLightParameters() const
{
	surfaceShaderProgram.use();
	const std::string prefix = "directionalLights[" + std::to_string(m_id) + "].";
	surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic", m_attenuationQuadratic);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", m_attenuationLinear);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", m_attenuationConstant);
}

unsigned int DirectionalLight::s_idCounter = 0;
