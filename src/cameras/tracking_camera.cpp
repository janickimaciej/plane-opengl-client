#include "cameras/tracking_camera.hpp"

#include "cameras/perspective_camera.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

TrackingCamera::TrackingCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
	const Model& model) :
	PerspectiveCamera { FoVDeg, aspectRatio, nearPlane, farPlane },
	m_model { model }
{ }

void TrackingCamera::use(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram)
{
	aimAtModel();
	Camera::use(surfaceShaderProgram, lightShaderProgram);
}

void TrackingCamera::aimAtModel()
{
	State state = getState();
	glm::vec3 modelPosition = m_model.getPosition();
	state.direction = glm::normalize(state.position - modelPosition);
	state.right = glm::normalize(glm::cross(glm::vec3 { 0, 1, 0 }, glm::vec3 { state.direction }));
	state.up = glm::normalize(glm::cross(glm::vec3 { state.direction }, glm::vec3 { state.right }));
	setState(state);
}
