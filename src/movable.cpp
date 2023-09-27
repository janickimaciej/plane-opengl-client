#include "movable.hpp"

#include "state.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <chrono> //tmp
#include <iostream> //tmp

State Movable::getState() const
{
	return m_state;
}

void Movable::setState(const State& newState)
{
	switch (m_st) //tmp b
	{
	case 0:
		if (m_state.direction().z < 0)
		{
			m_start = std::chrono::high_resolution_clock::now();
			m_st = 1;
		}
		break;
	case 1:
		if (m_state.direction().z > 0)
		{
			m_st = 2;
		}
		break;
	case 2:
		if (m_state.direction().z < 0)
		{
			auto stop = std::chrono::high_resolution_clock::now();
			long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - m_start).count();
			if (duration < 16000) break;
			if (duration < m_min) m_min = duration;
			if (duration > m_max) m_max = duration;
			m_count++;
			m_sum += duration;
			std::cout << "single:\t" << duration << '\n';
			std::cout << "avg:\t" << m_sum / m_count << '\n';
			std::cout << "count:\t" << m_count << '\n';
			std::cout << "min:\t" << m_min << '\n';
			std::cout << "max:\t" << m_max << '\n';
			std::cout << std::endl;
			m_start = std::chrono::high_resolution_clock::now();
			m_st = 1;
		}
		break;
	} //tmp e

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
