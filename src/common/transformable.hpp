#pragma once

#include "state.hpp"

#include <glm/glm.hpp>

namespace Common
{
	class Transformable
	{
	public:
		virtual State getState() const;
		virtual void setState(const State& newState);

		virtual void rotate(const glm::vec3& axis, float angleDeg); // locally
		virtual void resetRotation(); // locally
		virtual void translate(const glm::vec3& translation);

		virtual void rotatePitch(float angleDeg); // locally
		virtual void rotateYaw(float angleDeg); // locally
		virtual void rotateRoll(float angleDeg); // locally
		virtual void moveZ(float distance); // locally

		virtual ~Transformable() = default;
	
	protected:
		Transformable();
		glm::mat4 getMatrix() const;
		virtual void scale(float scaleRatio); // locally

	private:
		State m_state{};
		float m_scaleRatio = 1;
		glm::mat4 m_matrix{};

		void updateMatrix();
	};
};
