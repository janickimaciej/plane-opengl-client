#pragma once

#include "common/transformable.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Light : public Common::Transformable
	{
	public:
		virtual void updateShaders(const glm::mat4& modelMatrix) const = 0;
		void setColor(const glm::vec3& color);
		virtual ~Light() = default;

	protected:
		unsigned int m_id{};
		const ShaderProgram& m_surfaceShaderProgram;
		glm::vec3 m_color{};

		Light(unsigned int id, const ShaderProgram& surfaceShaderProgram, const glm::vec3& color);
		Light(const Light& light) = default;
		Light(Light&& light) = default;
		glm::vec3 getGlobalPosition(const glm::mat4& modelMatrix) const;
		glm::vec3 getGlobalDirection(const glm::mat4& modelMatrix) const;
	};
};
