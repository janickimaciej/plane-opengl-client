#include "scene.hpp"

Scene::Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	surfaceShaderProgram(surfaceShaderProgram), lightShaderProgram(lightShaderProgram) { }
