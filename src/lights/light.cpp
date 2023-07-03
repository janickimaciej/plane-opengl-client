#include "light.hpp"

Light::Light(const ShaderProgram& surfaceShaderProgram, unsigned int id, float attenuationQuadratic,
	float attenuationLinear, float attenuationConstant, glm::vec3 color) :
	surfaceShaderProgram(surfaceShaderProgram), id(id), attenuationQuadratic(attenuationQuadratic),
	attenuationLinear(attenuationLinear), attenuationConstant(attenuationConstant), color(color) { }

void Light::setColor(glm::vec3 color) {
	this->color = color;
	updateShaderLightParameters();
}
