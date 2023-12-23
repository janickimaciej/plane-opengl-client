#include "graphics/lights/directional_light.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	DirectionalLight::DirectionalLight(const ShaderProgram& surfaceShaderProgram,
		const glm::vec3& color) :
		Light{s_idCounter, surfaceShaderProgram, color}
	{
		++s_idCounter;
	}

	void DirectionalLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		m_surfaceShaderProgram.use();
		const std::string prefix = "directionalLights[" + std::to_string(m_id) + "].";
		
		m_surfaceShaderProgram.setUniform3f(prefix + "direction", getGlobalDirection(modelMatrix));
		m_surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
	}

	unsigned int DirectionalLight::s_idCounter = 0;
};
