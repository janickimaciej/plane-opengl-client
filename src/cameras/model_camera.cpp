#include "cameras/model_camera.hpp"

#include "cameras/perspective_camera.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

ModelCamera::ModelCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
	const Model& model) :
	PerspectiveCamera{FoVDeg, aspectRatio, nearPlane, farPlane},
	m_model{model}
{ }

glm::mat4 ModelCamera::getOriginMatrix() const
{
	return m_model.getModelMatrix();
}
