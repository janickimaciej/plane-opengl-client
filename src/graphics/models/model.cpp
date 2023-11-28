#include "graphics/models/model.hpp"

#include "common/transformable.hpp"
#include "common/state.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	void Model::render() const
	{
		m_surfaceShaderProgram.use();
		renderSurfaces();

		m_lightShaderProgram.use();
		renderLights();
	}

	glm::mat4 Model::getModelMatrix() const
	{
		return getMatrix();
	}

	glm::vec3 Model::getPosition() const
	{
		return getState().position;
	}

	void Model::scale(float scaleRatio)
	{
		Transformable::scale(scaleRatio);
	}

	Model::Model(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) :
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_lightShaderProgram{lightShaderProgram}
	{ }
};
