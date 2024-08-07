#pragma once

#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class WorldShading
	{
	public:
		WorldShading(const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram);
		void updateShaders() const;

		void setBackgroundColor(const glm::vec3& backgroundColor);
		void setAmbient(float ambient);
		void setFogGradient(float fogGradient);
		void setFogDensity(float fogDensity);

	private:
		glm::vec3 m_backgroundColor{};
		float m_ambient{};
		float m_fogGradient{};
		float m_fogDensity{};

		const ShaderProgram& m_surfaceShaderProgram;
		const ShaderProgram& m_lightShaderProgram;
	};
};
