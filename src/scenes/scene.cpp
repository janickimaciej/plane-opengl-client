#include "scenes/scene.hpp"

#include "graphics/shader_program.hpp"

Scene::Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager) :
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram},
	m_meshManager{meshManager},
	m_textureManager{textureManager}
{ }
