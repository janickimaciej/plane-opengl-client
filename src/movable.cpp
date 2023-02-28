#include "movable.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Movable::Movable() {
	updateMatrix();
}

void Movable::updateMatrix() {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(scaleRatio, scaleRatio, scaleRatio));

	float rotateMatrixT[16] = {
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		direction.x, direction.y, direction.z, 0,
		0, 0, 0, 1
	};
	glm::mat4 rotateMatrix = glm::make_mat4(rotateMatrixT);

	glm::mat4 translateMatrix = glm::translate(glm::mat4(1), position);

	matrix = translateMatrix*rotateMatrix*scaleMatrix;
}

void Movable::scale(float scaleRatio) {
	this->scaleRatio *= scaleRatio;
	updateMatrix();
}

void Movable::rotate(glm::vec3 axis, float angleDeg) {
	glm::mat4 transform = glm::rotate(glm::mat4(1), glm::radians(angleDeg), axis);
	direction = glm::normalize(transform*direction);
	right = glm::normalize(transform*right);
	up = glm::normalize(transform*up);
	updateMatrix();
}

void Movable::translate(glm::vec3 translation) {
	position += translation;
	updateMatrix();
}

void Movable::pitch(float angleDeg) {
	rotate(right, angleDeg);
}

void Movable::yaw(float angleDeg) {
	rotate(up, -angleDeg);
}

void Movable::roll(float angleDeg) {
	rotate(direction, -angleDeg);
}

void Movable::moveForwards(float distance) {
	translate(-distance*direction);
}

void Movable::moveBackwards(float distance) {
	translate(distance*direction);
}
