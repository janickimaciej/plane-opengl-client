#include "models/model.hpp"

#include "graphics/shader_program.hpp"
#include "transformable.hpp"
#include "state.hpp"

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
	Transformable::setState(newState);
	updateShaderLightMatrix();
}

void Model::scale(float scaleRatio)
{
	Transformable::scale(scaleRatio);
	updateShaderLightMatrix();
}

void Model::rotate(const glm::vec3& axis, float angleDeg)
{
	Transformable::rotate(axis, angleDeg);
	updateShaderLightMatrix();
}

void Model::resetRotation()
{
	Transformable::resetRotation();
	updateShaderLightMatrix();
}

void Model::translate(const glm::vec3& translation)
{
	Transformable::translate(translation);
	updateShaderLightMatrix();
}

void Model::rotatePitch(float angleDeg)
{
	Transformable::rotatePitch(angleDeg);
	updateShaderLightMatrix();
}

void Model::rotateYaw(float angleDeg)
{
	Transformable::rotateYaw(angleDeg);
	updateShaderLightMatrix();
}

void Model::rotateRoll(float angleDeg)
{
	Transformable::rotateRoll(angleDeg);
	updateShaderLightMatrix();
}

void Model::moveZ(float distance)
{
	Transformable::moveZ(distance);
	updateShaderLightMatrix();
}

Model::Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) :
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram}
{ }
