#ifndef MOVABLE
#define MOVABLE

#include "structs/state.hpp"
#include "shader_program.hpp"

class Movable {
protected:
	float scaleRatio = 1;
	State state;
	glm::mat4 matrix;
	
	Movable();
	void updateMatrix();
	virtual ~Movable() = default;
public:
	virtual void scale(float scaleRatio); // locally
	virtual void rotate(glm::vec3 axis, float angleDeg); // locally
	virtual void resetRotation(); // locally
	virtual void translate(glm::vec3 translation);

	virtual void pitch(float angleDeg); // locally
	virtual void yaw(float angleDeg); // locally
	virtual void roll(float angleDeg); // locally
	virtual void moveAlongZ(float distance); // locally
};

#endif
