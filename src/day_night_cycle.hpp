#ifndef DAY_NIGHT_CYCLE
#define DAY_NIGHT_CYCLE

#include "global_shading.hpp"
#include "models/directional_light_model.hpp"

class DayNightCycle {
	static float secondsPerDay;
	static float timeOfDay;
	static int day;
	static DirectionalLightModel* moon;

	DayNightCycle() { }
public:
	static void updateTimeOfDay();
	static void updateGlobalShading();
	static float getDayCoefficient();
	static float getFogCoefficient();

	static void setMoon(DirectionalLightModel* moon);
};

#endif
