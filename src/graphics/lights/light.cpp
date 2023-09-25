#include "graphics/lights/light.hpp"

#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

void Light::setColor(const glm::vec3& color)
{
	this->m_color = color;
	updateShaderLightParams();
}

Light::Light(const ShaderProgram& surfaceShaderProgram, unsigned int id, float attenuationQuadratic,
	float attenuationLinear, float attenuationConstant, const glm::vec3& color) :
	surfaceShaderProgram{surfaceShaderProgram},
	m_id{id},
	m_attenuationQuadratic{attenuationQuadratic},
	m_attenuationLinear{attenuationLinear},
	m_attenuationConstant{attenuationConstant},
	m_color{color}
{ }