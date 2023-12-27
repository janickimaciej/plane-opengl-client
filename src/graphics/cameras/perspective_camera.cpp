#include "graphics/cameras/perspective_camera.hpp"

#include "graphics/cameras/camera.hpp"
#include "graphics/shader_program.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	PerspectiveCamera::PerspectiveCamera(float FoVRad, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
		Camera{FoVRad, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram}
	{ }

	void PerspectiveCamera::updateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(m_FoVRad, m_aspectRatio, m_nearPlane, m_farPlane);
	}
};
