#include "graphics/lights/pointLight.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>
#include <string>

namespace Graphics
{
	const std::string prefix = "pointLights";

	PointLight::PointLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant) :
		Light{getAvailableId(surfaceShaderProgram), prefix, surfaceShaderProgram, color},
		m_attenuationQuadratic{attenuationQuadratic},
		m_attenuationLinear{attenuationLinear},
		m_attenuationConstant{attenuationConstant}
	{ }

	PointLight::PointLight(const PointLight& pointLight) :
		Light{getAvailableId(pointLight.m_surfaceShaderProgram), prefix,
			pointLight.m_surfaceShaderProgram, pointLight.m_color, pointLight.getState()},
		m_attenuationQuadratic{pointLight.m_attenuationQuadratic},
		m_attenuationLinear{pointLight.m_attenuationLinear},
		m_attenuationConstant{pointLight.m_attenuationConstant}
	{ }

	PointLight::PointLight(PointLight&& pointLight) noexcept :
		Light{pointLight.m_id, prefix, pointLight.m_surfaceShaderProgram, pointLight.m_color,
			pointLight.getState()},
		m_attenuationQuadratic{pointLight.m_attenuationQuadratic},
		m_attenuationLinear{pointLight.m_attenuationLinear},
		m_attenuationConstant{pointLight.m_attenuationConstant}
	{
		++m_isActive[m_id];
	}

	void PointLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		m_surfaceShaderProgram.use();
		m_surfaceShaderProgram.setUniform3f(m_prefix + "position", getGlobalPosition(modelMatrix));
		m_surfaceShaderProgram.setUniform3f(m_prefix + "color", m_color);
		m_surfaceShaderProgram.setUniform1f(m_prefix + "attenuationQuadratic",
			m_attenuationQuadratic);
		m_surfaceShaderProgram.setUniform1f(m_prefix + "attenuationLinear", m_attenuationLinear);
		m_surfaceShaderProgram.setUniform1f(m_prefix + "attenuationConstant",
			m_attenuationConstant);
	}

	PointLight::~PointLight()
	{
		--m_isActive[m_id];

		if (m_isActive[m_id] == 0)
		{
			m_surfaceShaderProgram.use();
			m_surfaceShaderProgram.setUniform1b(m_prefix + "isActive", false);
		}
	}
	
	std::array<int, PointLight::maxPointLightCount> PointLight::m_isActive{};

	unsigned int PointLight::getAvailableId(const ShaderProgram& surfaceShaderProgram)
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
