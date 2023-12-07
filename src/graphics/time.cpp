#include "graphics/time.hpp"

#include <glfw/glfw3.h>

#include <chrono>

namespace Graphics
{
	void Time::initialize()
	{
		update();
	}

	void Time::update()
	{
		std::chrono::time_point<std::chrono::system_clock> currentTime =
			std::chrono::system_clock::now();
		m_deltaTime = currentTime - m_time;
		m_time = currentTime;
	}

	int Time::getFPS()
	{
		return static_cast<int>(1.0f / m_deltaTime.count() + 0.5f);
	}
};
