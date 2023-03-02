#ifndef TIME
#define TIME

#include <GLFW/glfw3.h>

class Time {
	static float time;
	static float deltaTime;

	Time() { }
public:
	static void initializeTime();
	static void updateTime();
	static float getDeltaTime();
};

#endif
