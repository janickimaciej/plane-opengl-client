#ifndef DAY_NIGHT_CYCLE
#define DAY_NIGHT_CYCLE

#include "global_shading.hpp"
#include "models/directional_light_model.hpp"

class DayNightCycle {
	static float secondsPerDay;
	static float timeOfDay;
	static int day;
	static DirectionalLightModel* moon;

	DayNightCycle() = delete;
	static void updateTimeOfDay();
	static void updateGlobalShading(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	static float getLightCoefficient();
	static float getFogCoefficient();
	~DayNightCycle() = delete;
public:
	static void update(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);

	static void setMoon(DirectionalLightModel* moon);
};

#endif
