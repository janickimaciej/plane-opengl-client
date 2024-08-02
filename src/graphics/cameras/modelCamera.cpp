#include "graphics/cameras/modelCamera.hpp"

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	ModelCamera::ModelCamera(const Model& model, float fovRad, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const ShaderProgram& hudShaderProgram) :
		PerspectiveCamera{fovRad, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram,
			hudShaderProgram},
		m_model{model}
	{ }

	glm::mat4 ModelCamera::getCameraMatrix() const
	{
		return m_model.getModelMatrix() * getMatrix();
	}
};
