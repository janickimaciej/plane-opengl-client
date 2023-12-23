#include "graphics/lights/point_light.hpp"

namespace Graphics
{
	PointLight::PointLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant) :
		Light{s_idCounter, surfaceShaderProgram, color},
		m_attenuationQuadratic{attenuationQuadratic},
		m_attenuationLinear{attenuationLinear},
		m_attenuationConstant{attenuationConstant}
	{
		++s_idCounter;
	}

	void PointLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		m_surfaceShaderProgram.use();
		const std::string prefix = "pointLights[" + std::to_string(m_id) + "].";

		m_surfaceShaderProgram.setUniform3f(prefix + "position", getGlobalPosition(modelMatrix));
		m_surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic",
			m_attenuationQuadratic);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", m_attenuationLinear);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", m_attenuationConstant);
	}

	unsigned int PointLight::s_idCounter = 0;
};
