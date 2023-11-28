#include "graphics/time.hpp"

#include <glfw/glfw3.h>

namespace Graphics
{
	void Time::initializeTime()
	{
		updateTime();
	}

	void Time::updateTime()
	{
		float currentTime = (float)glfwGetTime();
		s_deltaTime = currentTime - s_time;
		s_time = currentTime;
	}

	float Time::getDeltaTime()
	{
		return s_deltaTime;
	}

	float Time::s_time{};
	float Time::s_deltaTime{};
};
