#pragma once

#include "common/config.hpp"
#include "graphics/lights/light.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>

namespace Graphics
{
	class PointLight : public Light
	{
	public:
		static constexpr std::size_t maxPointLightCount = 1 + 2 * Common::maxPlayerCount;

		PointLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
			float attenuationQuadratic, float attenuationLinear, float attenuationConstant);
		PointLight(const PointLight& pointLight);
		PointLight(PointLight&& pointLight) noexcept;
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~PointLight();

	protected:
		float m_attenuationQuadratic{};
		float m_attenuationLinear{};
		float m_attenuationConstant{};

	private:
		static std::array<int, maxPointLightCount> m_isActive;

		static unsigned int getAvailableId(const ShaderProgram& surfaceShaderProgram);
	};
};
