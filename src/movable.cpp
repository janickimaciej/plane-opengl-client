#include "movable.hpp"

#include "structs/state.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	glm::mat4 transform4 = glm::rotate(glm::mat4 { 1 }, glm::radians(angleDeg), axis);
	glm::mat3 transform3 { transform4 };
	m_state.right = transform3 * m_state.right;
	m_state.up = transform3 * m_state.up;
	m_state.direction = transform3 * m_state.direction;
	State::normalize(m_state);
	updateMatrix();
}

void Movable::resetRotation()
{
	m_state.right = glm::vec3 { 1, 0, 0 };
	m_state.up = glm::vec3 { 0, 1, 0 };
	m_state.direction = glm::vec3 { 0, 0, 1 };
	updateMatrix();
}

void Movable::translate(const glm::vec3& translation)
{
	m_state.position += translation;
	updateMatrix();
}

void Movable::pitch(float angleDeg)
{
	rotate(m_state.right, angleDeg);
}

void Movable::yaw(float angleDeg)
{
	rotate(m_state.up, -angleDeg);
}

void Movable::roll(float angleDeg)
{
	rotate(m_state.direction, -angleDeg);
}

void Movable::moveAlongZ(float distance)
{
	translate(distance * m_state.direction);
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
	glm::mat4 scaleMatrix = glm::scale(glm::mat4 { 1 },
		glm::vec3 { m_scaleRatio, m_scaleRatio, m_scaleRatio });
	m_matrix = State::objToMat(m_state) * scaleMatrix;
}
