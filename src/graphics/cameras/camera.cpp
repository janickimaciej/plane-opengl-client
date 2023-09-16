#include "graphics/cameras/camera.hpp"

#include "graphics/shader_program.hpp"
#include "movable.hpp"

#include <glm/glm.hpp>

void Camera::use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram)
{
	updateShaderMatrices(surfaceShaderProgram, lightShaderProgram);
}

Camera::Camera(const glm::mat4& projectionMatrix) :
	m_projectionMatrix{projectionMatrix}
{ }

void Camera::updateShaderMatrices(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) const
{
	glm::mat4 projectionViewMatrix = m_projectionMatrix * getViewMatrix();
	glm::vec3 cameraPosition = getCameraPosition();

	surfaceShaderProgram.use();
	surfaceShaderProgram.setUniformMatrix4f("projectionViewMatrix", projectionViewMatrix);
	surfaceShaderProgram.setUniform3f("cameraPosition", cameraPosition);

	lightShaderProgram.use();
	lightShaderProgram.setUniformMatrix4f("projectionViewMatrix", projectionViewMatrix);
	lightShaderProgram.setUniform3f("cameraPosition", cameraPosition);
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
