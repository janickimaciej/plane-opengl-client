#ifndef TIME
#define TIME

#include <GLFW/glfw3.h>

class Time {
	static float time;
	static float deltaTime;
public:
	Time() = delete;
	static void initializeTime();
	static void updateTime();
	static float getDeltaTime();
	~Time() = delete;
};

#endif
