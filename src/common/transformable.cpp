#include "common/transformable.hpp"

#include "common/state.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Common
{
	State Transformable::getState() const
	{
		return m_state;
	}

	void Transformable::setState(const State& newState)
	{
		m_state = newState;
		updateMatrix();
	}

	void Transformable::rotate(const glm::vec3& axis, float angleDeg)
	{
		glm::quat rotation = glm::angleAxis(glm::radians(angleDeg), axis);
		m_state.orientation = rotation * m_state.orientation;
		m_state.normalize();
		updateMatrix();
	}

	void Transformable::resetRotation()
	{
		m_state.orientation = glm::quat{1, 0, 0, 0};
		updateMatrix();
	}

	void Transformable::translate(const glm::vec3& translation)
	{
		m_state.position += translation;
		updateMatrix();
	}

	void Transformable::rotatePitch(float angleDeg)
	{
		rotate(m_state.right(), angleDeg);
	}

	void Transformable::rotateYaw(float angleDeg)
	{
		rotate(m_state.up(), -angleDeg);
	}

	void Transformable::rotateRoll(float angleDeg)
	{
		rotate(m_state.direction(), -angleDeg);
	}

	void Transformable::moveZ(float distance)
	{
		translate(distance * m_state.direction());
	}

	Transformable::Transformable()
	{
		updateMatrix();
	}

	glm::mat4 Transformable::getMatrix() const
	{
		return m_matrix;
	}

	void Transformable::scale(float scaleRatio)
	{
		this->m_scaleRatio *= scaleRatio;
		updateMatrix();
	}

	void Transformable::updateMatrix()
	{
		glm::mat4 scaleMatrix = glm::scale(glm::mat4{1}, glm::vec3{m_scaleRatio, m_scaleRatio,
			m_scaleRatio});
		m_matrix = m_state.matrix() * scaleMatrix;
	}
};
