#include "models/directional_light_model.hpp"

#include "lights/directional_light.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

DirectionalLightModel::DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, const glm::vec3& lightColor) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_light{surfaceShaderProgram, 0, 0, 1, lightColor}
{
	updateShaderLightMatrix();
}

void DirectionalLightModel::setLightColor(const glm::vec3& color)
{
	m_light.setColor(color);
}

void DirectionalLightModel::updateShaderLightMatrix() const
{
	m_light.updateShaderLightTranslation(getMatrix());
}

void DirectionalLightModel::renderSurfaces() const
{ }

void DirectionalLightModel::renderLights() const
{ }
