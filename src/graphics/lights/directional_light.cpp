#include "graphics/lights/directional_light.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <string>

DirectionalLight::DirectionalLight(const ShaderProgram& surfaceShaderProgram,
	float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
	const glm::vec3& color) :
	Light{s_idCounter, surfaceShaderProgram, attenuationQuadratic, attenuationLinear,
		attenuationConstant, color}
{
	++s_idCounter;
	updateShaderLightParams();
}

void DirectionalLight::updateShaderLightTranslation(const glm::mat4& modelMatrix) const
{
	m_surfaceShaderProgram.use();
	const std::string prefix = "directionalLights[" + std::to_string(m_id) + "].";
	m_surfaceShaderProgram.setUniform3f(prefix + "lightDirection",
		glm::normalize(glm::vec3{modelMatrix * glm::vec4{0, 0, 1, 0}}));
}

void DirectionalLight::updateShaderLightParams() const
{
	m_surfaceShaderProgram.use();
	const std::string prefix = "directionalLights[" + std::to_string(m_id) + "].";
	m_surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
	m_surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic", m_attenuationQuadratic);
	m_surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", m_attenuationLinear);
	m_surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", m_attenuationConstant);
}

unsigned int DirectionalLight::s_idCounter = 0;
