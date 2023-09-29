#include "movable.hpp"

#include "state.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

State Movable::getState() const
{
	return m_state;
}

void Movable::setState(const State& newState)
{
	m_state = newState;
	updateMatrix();
}

void Movable::scale(float scaleRatio)
{
	this->m_scaleRatio *= scaleRatio;
	updateMatrix();
}

void Movable::rotate(const glm::vec3& axis, float angleDeg)
{
	glm::quat rotation = glm::angleAxis(glm::radians(angleDeg), axis);
	m_state.orientation = rotation * m_state.orientation;
	m_state.normalize();
	updateMatrix();
}

void Movable::resetRotation()
{
	m_state.orientation = glm::quat{1, 0, 0, 0};
	updateMatrix();
}

void Movable::translate(const glm::vec3& translation)
{
	m_state.position += translation;
	updateMatrix();
}

void Movable::rotatePitch(float angleDeg)
{
	rotate(m_state.right(), angleDeg);
}

void Movable::rotateYaw(float angleDeg)
{
	rotate(m_state.up(), -angleDeg);
}

void Movable::rotateRoll(float angleDeg)
{
	rotate(m_state.direction(), -angleDeg);
}

void Movable::moveZ(float distance)
{
	translate(distance * m_state.direction());
}

Movable::Movable()
{
	updateMatrix();
}

glm::mat4 Movable::getMatrix() const
{
	return m_matrix;
}

void Movable::updateMatrix()
{
	glm::mat4 scaleMatrix = glm::scale(glm::mat4{1}, glm::vec3{m_scaleRatio, m_scaleRatio,
		m_scaleRatio});
	m_matrix = m_state.matrix() * scaleMatrix;
}
