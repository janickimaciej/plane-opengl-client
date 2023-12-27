#pragma once

#include <chrono>

namespace Graphics
{
	class Time
	{
	public:
		static void initialize();
		static void update();
		static float getDeltaTime();
		static int getFPS();
	
	private:
		static std::chrono::time_point<std::chrono::system_clock> m_time;
		static std::chrono::duration<float> m_deltaTime;
	};
};
