#pragma once

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color);
		DirectionalLight(const DirectionalLight& directionalLight) = default;
		DirectionalLight(DirectionalLight&& directionalLight) = default;
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~DirectionalLight() = default;

	private:
		static unsigned int s_idCounter;
	};
};
