#pragma once

#include "common/config.hpp"
#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>

namespace Graphics
{
	class SpotLight : public Light
	{
	public:
		static constexpr std::size_t airportLightCount = 8;
		static constexpr std::size_t maxSpotLightCount = airportLightCount +
			2 * Common::maxPlayerCount;

		SpotLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
			float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
			float cutoffInnerDeg, float cutoffOuterDeg);
		SpotLight(const SpotLight& spotLight);
		SpotLight(SpotLight&& spotLight) noexcept;
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~SpotLight();

	protected:
		float m_attenuationQuadratic{};
		float m_attenuationLinear{};
		float m_attenuationConstant{};
		float m_cutoffInnerDeg{};
		float m_cutoffOuterDeg{};

	private:
		static std::array<int, maxSpotLightCount> m_isActive;

		static unsigned int getAvailableId(const ShaderProgram& surfaceShaderProgram);
	};
};
