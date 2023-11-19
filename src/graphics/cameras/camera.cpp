#include "graphics/cameras/camera.hpp"

#include "graphics/shader_program.hpp"
#include "transformable.hpp"

#include <glm/glm.hpp>

void Camera::use(float aspectRatio)
{
	updateShaderMatrices(aspectRatio);
}

Camera::Camera(float FoVDeg, float nearPlane, float farPlane,
	const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	m_FoVDeg{FoVDeg},
	m_nearPlane{nearPlane},
	m_farPlane{farPlane},
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram}
{ }

void Camera::updateShaderMatrices(float aspectRatio)
{
	if (aspectRatio != m_aspectRatio)
	{
		m_aspectRatio = aspectRatio;
		updateProjectionMatrix();
	}
	glm::mat4 projectionViewMatrix = m_projectionMatrix * getViewMatrix();
	glm::vec3 cameraPosition = getCameraPosition();

	m_surfaceShaderProgram.use();
	m_surfaceShaderProgram.setUniformMatrix4f("projectionViewMatrix", projectionViewMatrix);
	m_surfaceShaderProgram.setUniform3f("cameraPosition", cameraPosition);

	m_lightShaderProgram.use();
	m_lightShaderProgram.setUniformMatrix4f("projectionViewMatrix", projectionViewMatrix);
	m_lightShaderProgram.setUniform3f("cameraPosition", cameraPosition);
}

glm::mat4 Camera::getOriginMatrix() const
{
	return glm::mat4{1};
}

glm::mat4 Camera::getCameraMatrix() const
{
	return getOriginMatrix() * getMatrix();
}

glm::vec3 Camera::getCameraPosition() const
{
	glm::vec4 cameraPosition = getCameraMatrix() * glm::vec4{0, 0, 0, 1};
	return glm::vec3{cameraPosition};
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::inverse(getCameraMatrix());
}
