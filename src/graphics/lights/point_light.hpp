#pragma once

#include "graphics/lights/light.hpp"

namespace Graphics
{
	class PointLight : public Light
	{
	public:
		PointLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color,
			float attenuationQuadratic, float attenuationLinear, float attenuationConstant);
		PointLight(const PointLight& pointlight) = default;
		PointLight(PointLight&& pointlight) = default;
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~PointLight() = default;

	protected:
		float m_attenuationQuadratic{};
		float m_attenuationLinear{};
		float m_attenuationConstant{};

	private:
		static unsigned int s_idCounter;
	};
};
