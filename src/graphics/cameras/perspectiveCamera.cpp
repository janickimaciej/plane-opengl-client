#include "graphics/cameras/perspectiveCamera.hpp"

#include "graphics/cameras/camera.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	PerspectiveCamera::PerspectiveCamera(float fovRad, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const ShaderProgram& hudShaderProgram) :
		Camera{nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram, hudShaderProgram},
		m_fovRad{fovRad}
	{ }

	void PerspectiveCamera::updateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(m_fovRad, m_aspectRatio, m_nearPlane, m_farPlane);
	}
};
