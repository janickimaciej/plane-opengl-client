#pragma once

namespace Graphics
{
	class Time
	{
	public:
		Time() = delete;
		static void initializeTime();
		static void updateTime();
		static float getDeltaTime();
		~Time() = delete;
	
	private:
		static float s_time;
		static float s_deltaTime;
	};
};
