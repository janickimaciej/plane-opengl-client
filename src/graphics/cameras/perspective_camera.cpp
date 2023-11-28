#include "graphics/cameras/perspective_camera.hpp"

#include "graphics/cameras/camera.hpp"
#include "graphics/shader_program.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	PerspectiveCamera::PerspectiveCamera(float FoVDeg, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
		Camera{FoVDeg, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram}
	{ }

	void PerspectiveCamera::updateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(glm::radians(m_FoVDeg), m_aspectRatio, m_nearPlane,
			m_farPlane);
	}
};
