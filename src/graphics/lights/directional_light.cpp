#include "graphics/lights/directional_light.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>
#include <string>

namespace Graphics
{
	const std::string prefix = "directionalLights";

	DirectionalLight::DirectionalLight(const ShaderProgram& surfaceShaderProgram,
		const glm::vec3& color) :
		Light{getAvailableId(surfaceShaderProgram), prefix, surfaceShaderProgram, color}
	{ }

	DirectionalLight::DirectionalLight(const DirectionalLight& directionalLight) :
		Light{getAvailableId(directionalLight.m_surfaceShaderProgram), prefix,
			directionalLight.m_surfaceShaderProgram, directionalLight.m_color,
			directionalLight.getState()}
	{ }

	DirectionalLight::DirectionalLight(DirectionalLight&& directionalLight) noexcept :
		Light{directionalLight.m_id, prefix, directionalLight.m_surfaceShaderProgram,
			directionalLight.m_color, directionalLight.getState()}
	{
		++m_isActive[m_id];
	}

	void DirectionalLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		m_surfaceShaderProgram.use();
		m_surfaceShaderProgram.setUniform3f(m_prefix + "direction",
			getGlobalDirection(modelMatrix));
		m_surfaceShaderProgram.setUniform3f(m_prefix + "color", m_color);
	}

	DirectionalLight::~DirectionalLight()
	{
		--m_isActive[m_id];

		if (m_isActive[m_id] == 0)
		{
			m_surfaceShaderProgram.use();
			m_surfaceShaderProgram.setUniform1b(m_prefix + "isActive", false);
		}
	}
	
	std::array<int, DirectionalLight::maxDirectionalLightCount> DirectionalLight::m_isActive{};

	unsigned int DirectionalLight::getAvailableId(const ShaderProgram& surfaceShaderProgram)
	{
		unsigned int newId{};
		bool found = false;
		for (std::size_t i = 0; i < m_isActive.size(); ++i)
		{
			if (m_isActive.at(i) == 0)
			{
				++m_isActive.at(i);
				newId = static_cast<unsigned int>(i);
				found = true;
				break;
			}
		}
		assert(found);

		surfaceShaderProgram.use();
		surfaceShaderProgram.setUniform1b(prefix + "[" + std::to_string(newId) + "].isActive",
			true);

		return newId;
	}
};
