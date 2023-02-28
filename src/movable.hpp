#ifndef MOVABLE
#define MOVABLE

#include <glm/glm.hpp>
#include "shader_program.hpp"

class Movable {
protected:
	float scaleRatio = 1;
	glm::vec4 direction = glm::vec4(0, 0, 1, 0);
	glm::vec4 right = glm::vec4(1, 0, 0, 0);
	glm::vec4 up = glm::vec4(0, 1, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::mat4 matrix;

	void updateMatrix();
	Movable();
public:
	virtual void scale(float scaleRatio); // locally
	virtual void rotate(glm::vec3 axis, float angleDeg); // locally
	virtual void translate(glm::vec3 translation);

	virtual void pitch(float angleDeg); // locally
	virtual void yaw(float angleDeg); // locally
	virtual void roll(float angleDeg); // locally
	virtual void moveForwards(float distance); // locally
	virtual void moveBackwards(float distance); // locally

	virtual ~Movable() { }
};

#endif
