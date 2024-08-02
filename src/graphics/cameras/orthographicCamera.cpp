#include "graphics/cameras/orthographicCamera.hpp"

namespace Graphics
{
	OrthographicCamera::OrthographicCamera(float width, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const ShaderProgram& hudShaderProgram) :
		Camera{nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram, hudShaderProgram},
		m_width{width}
	{ }

	void OrthographicCamera::updateProjectionMatrix()
	{
		float height = m_width / m_aspectRatio;
		m_projectionMatrix = glm::ortho(-m_width / 2, m_width / 2, -height / 2, height / 2,
			m_nearPlane, m_farPlane);
	}
};
