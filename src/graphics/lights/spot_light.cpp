#include "graphics/lights/spot_light.hpp"

#include "graphics/lights/mesh_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	SpotLight::SpotLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, const glm::vec3& color,
		float cutoffInnerDeg, float cutoffOuterDeg, const Submodel& submodel) :
		MeshLight{s_idCounter, surfaceShaderProgram, attenuationQuadratic, attenuationLinear,
			attenuationConstant, color, submodel},
		m_cutoffInnerDeg{cutoffInnerDeg},
		m_cutoffOuterDeg{cutoffOuterDeg}
	{
		++s_idCounter;
	}

	void SpotLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		m_surfaceShaderProgram.use();
		const std::string prefix = "spotLights[" + std::to_string(m_id) + "].";

		glm::vec3 lightDirection = glm::normalize(glm::vec3
		{
			modelMatrix * m_submodel.getMatrix() * glm::vec4{0, 0, 1, 0}
		});
		m_surfaceShaderProgram.setUniform3f(prefix + "lightDirection", lightDirection);

		glm::vec3 lightPosition = modelMatrix * m_submodel.getMatrix() * glm::vec4{0, 0, 0, 1};
		m_surfaceShaderProgram.setUniform3f(prefix + "lightPosition", lightPosition);

		m_surfaceShaderProgram.setUniform1f(prefix + "cutoffInnerRad", glm::radians(m_cutoffInnerDeg));
		m_surfaceShaderProgram.setUniform1f(prefix + "cutoffOuterRad", glm::radians(m_cutoffOuterDeg));
		m_surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic", m_attenuationQuadratic);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", m_attenuationLinear);
		m_surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", m_attenuationConstant);
	}

	unsigned int SpotLight::s_idCounter = 0;
};
