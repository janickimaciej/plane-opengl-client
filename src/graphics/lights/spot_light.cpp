#include "graphics/lights/spot_light.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	SpotLight::SpotLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		float cutoffInnerDeg, float cutoffOuterDeg) :
		Light{s_idCounter, surfaceShaderProgram, color},
		m_attenuationQuadratic{attenuationQuadratic},
		m_attenuationLinear{attenuationLinear},
		m_attenuationConstant{attenuationConstant},
		m_cutoffInnerDeg{cutoffInnerDeg},
		m_cutoffOuterDeg{cutoffOuterDeg}
	{
		++s_idCounter;
	}

	void SpotLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		m_surfaceShaderProgram.use();
		const std::string prefix = "spotLights[" + std::to_string(m_id) + "].";

		m_surfaceShaderProgram.setUniform3f(prefix + "direction", getGlobalDirection(modelMatrix));
		m_surfaceShaderProgram.setUniform3f(prefix + "position", getGlobalPosition(modelMatrix));
		m_surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic",
			m_attenuationQuadratic);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", m_attenuationLinear);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", m_attenuationConstant);
		m_surfaceShaderProgram.setUniform1f(prefix + "cutoffInnerRad",
			glm::radians(m_cutoffInnerDeg));
		m_surfaceShaderProgram.setUniform1f(prefix + "cutoffOuterRad",
			glm::radians(m_cutoffOuterDeg));
	}

	unsigned int SpotLight::s_idCounter = 0;
};
