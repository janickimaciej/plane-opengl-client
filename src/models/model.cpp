#include "models/model.hpp"

#include "graphics/shader_program.hpp"
#include "transformable.hpp"
#include "state.hpp"

#include <glm/glm.hpp>

void Model::tryInitializing()
{
	if (!isInitialized)
	{
		initialize();
		isInitialized = true;
	}
}

void Model::render() const
{
	m_surfaceShaderProgram.use();
	renderSurfaces();

	m_lightShaderProgram.use();
	renderLights();
}

glm::mat4 Model::getModelMatrix() const
{
	return getMatrix();
}

glm::vec3 Model::getPosition() const
{
	return getState().position;
}

void Model::scale(float scaleRatio)
{
	Transformable::scale(scaleRatio);
}

Model::Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager) :
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram},
	m_meshManager{meshManager},
	m_textureManager{textureManager}
{ }
