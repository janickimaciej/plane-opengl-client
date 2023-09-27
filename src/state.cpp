#include "state.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <array>

State::State(const std::array<float, stateLength>& arr)
{
	position.x = arr[0];
	position.y = arr[1];
	position.z = arr[2];
	orientation.w = arr[3];
	orientation.x = arr[4];
	orientation.y = arr[5];
	orientation.z = arr[6];
	velocity.x = arr[7];
	velocity.y = arr[8];
	velocity.z = arr[9];
	angVelocityRad.x = arr[10];
	angVelocityRad.y = arr[11];
	angVelocityRad.z = arr[12];
}

void State::toArr(std::array<float, stateLength>& arr) const
{
	arr[0] = position.x;
	arr[1] = position.y;
	arr[2] = position.z;
	arr[3] = orientation.w;
	arr[4] = orientation.x;
	arr[5] = orientation.y;
	arr[6] = orientation.z;
	arr[7] = velocity.x;
	arr[8] = velocity.y;
	arr[9] = velocity.z;
	arr[10] = angVelocityRad.x;
	arr[11] = angVelocityRad.y;
	arr[12] = angVelocityRad.z;
}

glm::mat4 State::matrix() const
{
	glm::mat4 orientationMatrix = glm::mat4_cast(orientation);
	glm::mat4 positionMatrix = glm::translate(glm::mat4{1}, position);
	return positionMatrix * orientationMatrix;
}

glm::vec3 State::right() const
{
	return orientation * glm::vec3{1, 0, 0};
}

glm::vec3 State::up() const
{
	return orientation * glm::vec3{0, 1, 0};
}

glm::vec3 State::direction() const
{
	return orientation * glm::vec3{0, 0, 1};
}

void State::normalize()
{
	orientation = glm::normalize(orientation);
}
