#include "graphics/worldShading.hpp"

#include "graphics/shaderProgram.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Graphics
{
	WorldShading::WorldShading(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) :
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_lightShaderProgram{lightShaderProgram}
	{ }

	void WorldShading::updateShaders() const
	{
		m_surfaceShaderProgram.use();
		m_surfaceShaderProgram.setUniform3f("worldShading.backgroundColor", m_backgroundColor);
		m_surfaceShaderProgram.setUniform1f("worldShading.ambient", m_ambient);
		m_surfaceShaderProgram.setUniform1f("worldShading.fogGradient", m_fogGradient);
		m_surfaceShaderProgram.setUniform1f("worldShading.fogDensity", m_fogDensity);

		m_lightShaderProgram.use();
		m_lightShaderProgram.setUniform3f("worldShading.backgroundColor", m_backgroundColor);
		m_lightShaderProgram.setUniform1f("worldShading.fogGradient", m_fogGradient);
		m_lightShaderProgram.setUniform1f("worldShading.fogDensity", m_fogDensity);

		glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void WorldShading::setBackgroundColor(const glm::vec3& backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

	void WorldShading::setAmbient(float ambient)
	{
		m_ambient = ambient;
	}

	void WorldShading::setFogGradient(float fogGradient)
	{
		m_fogGradient = fogGradient;
	}

	void WorldShading::setFogDensity(float fogDensity)
	{
		m_fogDensity = fogDensity;
	}
};
