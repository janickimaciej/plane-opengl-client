#include "graphics/models/directionalLightModel.hpp"

#include "graphics/lights/directionalLight.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"

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
