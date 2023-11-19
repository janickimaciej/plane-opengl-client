#include "graphics/cameras/model_camera.hpp"

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

ModelCamera::ModelCamera(float FoVDeg, float nearPlane, float farPlane,
	const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Model& model) :
	PerspectiveCamera{FoVDeg, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram},
	m_model{model}
{ }

glm::mat4 ModelCamera::getOriginMatrix() const
{
	return m_model.getModelMatrix();
}
