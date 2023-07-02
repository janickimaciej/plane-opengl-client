#include "time.hpp"

float Time::time;
float Time::deltaTime;

void Time::initializeTime() {
	updateTime();
}

void Time::updateTime() {
	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - time;
	time = currentTime;
}

float Time::getDeltaTime() {
	return deltaTime;
}
