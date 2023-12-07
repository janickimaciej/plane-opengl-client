#pragma once

#include <chrono>

namespace Graphics
{
	class Time
	{
	public:
		void initialize();
		void update();
		int getFPS();
	
	private:
		std::chrono::time_point<std::chrono::system_clock> m_time{};
		std::chrono::duration<float> m_deltaTime{};
	};
};
