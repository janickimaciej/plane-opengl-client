#include "global_shading.hpp"

#include "shader_program.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

void GlobalShading::use(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram)
{
	updateShaderGlobalShading(surfaceShaderProgram, lightShaderProgram);
	glClearColor(s_backgroundColor.r, s_backgroundColor.g, s_backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlobalShading::setBackgroundColor(const glm::vec3& backgroundColor)
{
	GlobalShading::s_backgroundColor = backgroundColor;
}

void GlobalShading::setAmbient(float ambient)
{
	GlobalShading::s_ambient = ambient;
}

void GlobalShading::setFogGradient(float fogGradient)
{
	GlobalShading::s_fogGradient = fogGradient;
}

void GlobalShading::setFogDensity(float fogDensity)
{
	GlobalShading::s_fogDensity = fogDensity;
}

glm::vec3 GlobalShading::s_backgroundColor {};
float GlobalShading::s_ambient {};
float GlobalShading::s_fogGradient {};
float GlobalShading::s_fogDensity {};

void GlobalShading::updateShaderGlobalShading(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram)
{
	surfaceShaderProgram.use();
	surfaceShaderProgram.setUniform3f("globalShading.backgroundColor", s_backgroundColor);
	surfaceShaderProgram.setUniform1f("globalShading.ambient", s_ambient);
	surfaceShaderProgram.setUniform1f("globalShading.fogGradient", s_fogGradient);
	surfaceShaderProgram.setUniform1f("globalShading.fogDensity", s_fogDensity);

	lightShaderProgram.use();
	lightShaderProgram.setUniform3f("globalShading.backgroundColor", s_backgroundColor);
	lightShaderProgram.setUniform1f("globalShading.fogGradient", s_fogGradient);
	lightShaderProgram.setUniform1f("globalShading.fogDensity", s_fogDensity);
}
