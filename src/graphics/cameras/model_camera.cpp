#include "graphics/cameras/model_camera.hpp"

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	ModelCamera::ModelCamera(const Model& model, float FoVRad, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const ShaderProgram& hudShaderProgram) :
		PerspectiveCamera{FoVRad, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram,
			hudShaderProgram},
		m_model{model}
	{ }

	glm::mat4 ModelCamera::getCameraMatrix() const
	{
		return m_model.getModelMatrix() * getMatrix();
	}
};
