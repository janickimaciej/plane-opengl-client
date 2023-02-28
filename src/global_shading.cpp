#include "global_shading.hpp"
#include <glad/glad.h>

glm::vec3 GlobalShading::backgroundColor;
float GlobalShading::ambient;
float GlobalShading::fogGradient;
float GlobalShading::fogDensity;

void GlobalShading::updateShaderGlobalShading(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) {
	surfaceShaderProgram.use();
	surfaceShaderProgram.setUniform3f("globalShading.backgroundColor", backgroundColor);
	surfaceShaderProgram.setUniform1f("globalShading.ambient", ambient);
	surfaceShaderProgram.setUniform1f("globalShading.fogGradient", fogGradient);
	surfaceShaderProgram.setUniform1f("globalShading.fogDensity", fogDensity);

	lightShaderProgram.use();
	lightShaderProgram.setUniform3f("globalShading.backgroundColor", backgroundColor);
	lightShaderProgram.setUniform1f("globalShading.ambient", ambient);
	lightShaderProgram.setUniform1f("globalShading.fogGradient", fogGradient);
	lightShaderProgram.setUniform1f("globalShading.fogDensity", fogDensity);
}

void GlobalShading::use(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) {
	updateShaderGlobalShading(surfaceShaderProgram, lightShaderProgram);
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::vec3 GlobalShading::getBackgroundColor() {
	return backgroundColor;
}

void GlobalShading::setBackgroundColor(glm::vec3 backgroundColor) {
	GlobalShading::backgroundColor = backgroundColor;
}

void GlobalShading::setAmbient(float ambient) {
	GlobalShading::ambient = ambient;
}

void GlobalShading::setFogGradient(float fogGradient) {
	GlobalShading::fogGradient = fogGradient;
}

void GlobalShading::setFogDensity(float fogDensity) {
	GlobalShading::fogDensity = fogDensity;
}
