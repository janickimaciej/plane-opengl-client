#include "time.hpp"

float Time::time;
float Time::deltaTime;

void Time::updateTime() {
	float currentTime = glfwGetTime();
	deltaTime = currentTime - time;
	time = currentTime;
}

float Time::getDeltaTime() {
	return deltaTime;
}
