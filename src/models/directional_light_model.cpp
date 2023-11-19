#include "models/directional_light_model.hpp"

#include "graphics/lights/directional_light.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

#include <memory>

DirectionalLightModel::DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
	AssetManager<const Texture>& textureManager, const glm::vec3& lightColor) :
	Model{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager},
	m_lightColor{lightColor}
{ }

void DirectionalLightModel::initialize()
{
	m_light = std::make_unique<DirectionalLight>(m_surfaceShaderProgram, 0, 0, 1, m_lightColor);
}

void DirectionalLightModel::setLightColor(const glm::vec3& color)
{
	tryInitializing();
	m_light->setColor(color);
}

void DirectionalLightModel::updateShaders()
{
	tryInitializing();
	m_light->updateShaders(getMatrix());
}

void DirectionalLightModel::renderSurfaces() const
{ }

void DirectionalLightModel::renderLights() const
{ }
