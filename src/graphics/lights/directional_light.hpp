#pragma once

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>

namespace Graphics
{
	class DirectionalLight : public Light
	{
	public:
		static constexpr std::size_t maxDirectionalLightCount = 2;

		DirectionalLight(const ShaderProgram& surfaceShaderProgram, const glm::vec3& color);
		DirectionalLight(const DirectionalLight& directionalLight);
		DirectionalLight(DirectionalLight&& directionalLight) noexcept;
		virtual void updateShaders(const glm::mat4& modelMatrix) const override;
		virtual ~DirectionalLight();

	private:
		static std::array<int, maxDirectionalLightCount> m_isActive;

		static unsigned int getAvailableId(const ShaderProgram& surfaceShaderProgram);
	};
};
