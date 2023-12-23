#pragma once

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class SpotLight : public Light
	{
	public:
		SpotLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
			float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
			float cutoffInnerDeg, float cutoffOuterDeg);
		SpotLight(const SpotLight& spotlight) = default;
		SpotLight(SpotLight&& spotlight) = default;
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~SpotLight() = default;

	protected:
		float m_attenuationQuadratic{};
		float m_attenuationLinear{};
		float m_attenuationConstant{};
		float m_cutoffInnerDeg{};
		float m_cutoffOuterDeg{};

	private:
		static unsigned int s_idCounter;
	};
};
