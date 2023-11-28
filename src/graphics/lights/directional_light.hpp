#pragma once

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
			float attenuationLinear, float attenuationConstant, const glm::vec3& color);
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~DirectionalLight() = default;

	private:
		static unsigned int s_idCounter;
	};
};
