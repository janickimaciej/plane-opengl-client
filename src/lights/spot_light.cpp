#include "lights/spot_light.hpp"

#include "lights/mesh_light.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

#include <string>

SpotLight::SpotLight(const ShaderProgram& surfaceShaderProgram, const Mesh& mesh,
	float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
	const glm::vec3& color, float cutoffInnerDeg, float cutoffOuterDeg,
	const glm::mat4& modelMatrix) :
	MeshLight{surfaceShaderProgram, s_idCounter, mesh, attenuationQuadratic, attenuationLinear,
		attenuationConstant, color},
	m_cutoffInnerDeg{cutoffInnerDeg},
	m_cutoffOuterDeg{cutoffOuterDeg}
{
	++s_idCounter;
	updateShaderLightParams();
	updateShaderLightTranslation(modelMatrix);
}

void SpotLight::updateShaderLightTranslation(const glm::mat4& modelMatrix) const
{
	surfaceShaderProgram.use();
	const std::string prefix = "spotLights[" + std::to_string(m_id) + "].";

	glm::vec3 lightDirection = glm::normalize(glm::vec3
	{
		modelMatrix * m_meshInstance.getMatrix() * glm::vec4{0, 0, 1, 0}
	});
	surfaceShaderProgram.setUniform3f(prefix + "lightDirection", lightDirection);

	glm::vec3 lightPosition = modelMatrix * m_meshInstance.getMatrix() * glm::vec4{0, 0, 0, 1};
	surfaceShaderProgram.setUniform3f(prefix + "lightPosition", lightPosition);
}

void SpotLight::updateShaderLightParams() const
{
	surfaceShaderProgram.use();
	const std::string prefix = "spotLights[" + std::to_string(m_id) + "].";
	surfaceShaderProgram.setUniform1f(prefix + "cutoffInnerRad", glm::radians(m_cutoffInnerDeg));
	surfaceShaderProgram.setUniform1f(prefix + "cutoffOuterRad", glm::radians(m_cutoffOuterDeg));
	surfaceShaderProgram.setUniform3f(prefix + "color", m_color);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationQuadratic", m_attenuationQuadratic);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationLinear", m_attenuationLinear);
	surfaceShaderProgram.setUniform1f(prefix + "attenuationConstant", m_attenuationConstant);
}

unsigned int SpotLight::s_idCounter = 0;
