#include "scenes/scene.hpp"

#include "graphics/shader_program.hpp"

Scene::Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram}
{ }
