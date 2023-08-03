#include "models/model.hpp"

#include "movable.hpp"
#include "shader_program.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

void Model::render() const
{
	m_surfaceShaderProgram.use();
	renderSurfaces();

	m_lightShaderProgram.use();
	renderLights();
}

glm::mat4 Model::getModelMatrix() const
{
	return m_matrix;
}

glm::vec3 Model::getPosition() const
{
	return getState().position;
}

void Model::setState(State newState)
{
	Movable::setState(newState);
	updateShaderLightMatrix();
}

void Model::scale(float scaleRatio)
{
	Movable::scale(scaleRatio);
	updateShaderLightMatrix();
}

void Model::rotate(glm::vec3 axis, float angleDeg)
{
	Movable::rotate(axis, angleDeg);
	updateShaderLightMatrix();
}

void Model::resetRotation()
{
	Movable::resetRotation();
	updateShaderLightMatrix();
}

void Model::translate(glm::vec3 translation)
{
	Movable::translate(translation);
	updateShaderLightMatrix();
}

void Model::pitch(float angleDeg)
{
	Movable::pitch(angleDeg);
	updateShaderLightMatrix();
}

void Model::yaw(float angleDeg)
{
	Movable::yaw(angleDeg);
	updateShaderLightMatrix();
}

void Model::roll(float angleDeg)
{
	Movable::roll(angleDeg);
	updateShaderLightMatrix();
}

void Model::moveAlongZ(float distance)
{
	Movable::moveAlongZ(distance);
	updateShaderLightMatrix();
}

Model::Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	m_surfaceShaderProgram { surfaceShaderProgram },
	m_lightShaderProgram { lightShaderProgram }
{ }
