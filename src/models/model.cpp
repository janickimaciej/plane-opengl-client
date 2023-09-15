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
	return getMatrix();
}

glm::vec3 Model::getPosition() const
{
	return getState().position;
}

void Model::setState(const State& newState)
{
	Movable::setState(newState);
	updateShaderLightMatrix();
}

void Model::scale(float scaleRatio)
{
	Movable::scale(scaleRatio);
	updateShaderLightMatrix();
}

void Model::rotate(const glm::vec3& axis, float angleDeg)
{
	Movable::rotate(axis, angleDeg);
	updateShaderLightMatrix();
}

void Model::resetRotation()
{
	Movable::resetRotation();
	updateShaderLightMatrix();
}

void Model::translate(const glm::vec3& translation)
{
	Movable::translate(translation);
	updateShaderLightMatrix();
}

void Model::rotatePitch(float angleDeg)
{
	Movable::rotatePitch(angleDeg);
	updateShaderLightMatrix();
}

void Model::rotateYaw(float angleDeg)
{
	Movable::rotateYaw(angleDeg);
	updateShaderLightMatrix();
}

void Model::rotateRoll(float angleDeg)
{
	Movable::rotateRoll(angleDeg);
	updateShaderLightMatrix();
}

void Model::moveZ(float distance)
{
	Movable::moveZ(distance);
	updateShaderLightMatrix();
}

Model::Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram}
{ }
