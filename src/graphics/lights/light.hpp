#pragma once

#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Light
	{
	public:
		virtual void updateShaders(const glm::mat4& modelMatrix) const = 0;
		void setColor(const glm::vec3& color);
		virtual ~Light() = default;

	protected:
		unsigned int m_id{};
		const ShaderProgram& m_surfaceShaderProgram;
		float m_attenuationQuadratic{};
		float m_attenuationLinear{};
		float m_attenuationConstant{};
		glm::vec3 m_color{};

		Light(unsigned int id, const ShaderProgram& surfaceShaderProgram,
			float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
			const glm::vec3& color);
		Light(const Light& light) = default;
		Light(Light&& light) = default;
	};
};
