#include "movable.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Movable::Movable() {
	updateMatrix();
}

void Movable::updateMatrix() {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(scaleRatio, scaleRatio, scaleRatio));

	float rotateMatrixT[16] = {
		state.right.x, state.right.y, state.right.z, 0,
		state.up.x, state.up.y, state.up.z, 0,
		state.direction.x, state.direction.y, state.direction.z, 0,
		0, 0, 0, 1
	};
	glm::mat4 rotateMatrix = glm::make_mat4(rotateMatrixT);

	glm::mat4 translateMatrix = glm::translate(glm::mat4(1), state.position);

	matrix = translateMatrix*rotateMatrix*scaleMatrix;
}

void Movable::scale(float scaleRatio) {
	this->scaleRatio *= scaleRatio;
	updateMatrix();
}

void Movable::rotate(glm::vec3 axis, float angleDeg) {
	glm::mat4 transform4 = glm::rotate(glm::mat4(1), glm::radians(angleDeg), axis);
	glm::mat3 transform3 = glm::mat3(transform4);
	state.right = glm::normalize(transform3*state.right);
	state.up = glm::normalize(transform3*state.up);
	state.direction = glm::normalize(transform3*state.direction);
	updateMatrix();
}

void Movable::resetRotation() {
	state.right = glm::vec3(1, 0, 0);
	state.up = glm::vec3(0, 1, 0);
	state.direction = glm::vec3(0, 0, 1);
	updateMatrix();
}

void Movable::translate(glm::vec3 translation) {
	state.position += translation;
	updateMatrix();
}

void Movable::pitch(float angleDeg) {
	rotate(state.right, angleDeg);
}

void Movable::yaw(float angleDeg) {
	rotate(state.up, -angleDeg);
}

void Movable::roll(float angleDeg) {
	rotate(state.direction, -angleDeg);
}

void Movable::moveAlongZ(float distance) {
	translate(distance*state.direction);
}
