#include "graphics/lights/light.hpp"

#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	void Light::setColor(const glm::vec3& color)
	{
		this->m_color = color;
	}

	Light::Light(unsigned int id, const ShaderProgram& surfaceShaderProgram,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		const glm::vec3& color) :
		m_id{id},
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_attenuationQuadratic{attenuationQuadratic},
		m_attenuationLinear{attenuationLinear},
		m_attenuationConstant{attenuationConstant},
		m_color{color}
	{ }
};
