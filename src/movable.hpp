#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "structs/state.hpp"

#include <glm/glm.hpp>

class Movable
{
public:
	virtual State getState() const;
	virtual void setState(const State& newState);

	virtual void scale(float scaleRatio); // locally
	virtual void rotate(const glm::vec3& axis, float angleDeg); // locally
	virtual void resetRotation(); // locally
	virtual void translate(const glm::vec3& translation);

	virtual void rotatePitch(float angleDeg); // locally
	virtual void rotateYaw(float angleDeg); // locally
	virtual void rotateRoll(float angleDeg); // locally
	virtual void moveZ(float distance); // locally
	
protected:
	Movable();
	glm::mat4 getMatrix() const;
	virtual ~Movable() = default;

private:
	State m_state{};
	float m_scaleRatio = 1;
	glm::mat4 m_matrix{};

	void updateMatrix();
};

#endif
