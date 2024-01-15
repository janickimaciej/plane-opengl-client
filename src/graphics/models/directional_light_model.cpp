#include "graphics/models/directional_light_model.hpp"

#include "graphics/lights/directional_light.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	DirectionalLightModel::DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
		const glm::vec3& lightColor) :
		m_light{surfaceShaderProgram, lightColor}
	{ }

	void DirectionalLightModel::setLightColor(const glm::vec3& color)
	{
		m_light.setColor(color);
	}

	void DirectionalLightModel::updateShaders()
	{
		m_light.updateShaders(getMatrix());
	}

	void DirectionalLightModel::render() const
	{ }
};
