#include "graphics/lights/light.hpp"

#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	void Light::setColor(const glm::vec3& color)
	{
		m_color = color;
	}

	Light::Light(unsigned int id, const ShaderProgram& surfaceShaderProgram,
		const glm::vec3& color) :
		m_id{id},
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_color{color}
	{ }

	glm::vec3 Light::getGlobalPosition(const glm::mat4& modelMatrix) const
	{
		return glm::vec3{modelMatrix * glm::vec4{getState().position, 1}};
	}

	glm::vec3 Light::getGlobalDirection(const glm::mat4& modelMatrix) const
	{
		return glm::normalize(glm::mat3{modelMatrix} * getState().direction());
	}
};
