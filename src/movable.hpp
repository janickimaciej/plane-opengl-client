#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "structs/state.hpp"

#include <glm/glm.hpp>

class Movable
{
public:
	virtual State getState() const;
	virtual void setState(State newState);

	virtual void scale(float scaleRatio); // locally
	virtual void rotate(glm::vec3 axis, float angleDeg); // locally
	virtual void resetRotation(); // locally
	virtual void translate(glm::vec3 translation);

	virtual void pitch(float angleDeg); // locally
	virtual void yaw(float angleDeg); // locally
	virtual void roll(float angleDeg); // locally
	virtual void moveAlongZ(float distance); // locally
	
protected:
	float m_scaleRatio = 1;
	glm::mat4 m_matrix {};
	
	Movable();
	void updateMatrix();
	virtual ~Movable() = default;

private:
	State m_state {};
};

#endif
