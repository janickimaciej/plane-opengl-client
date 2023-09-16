#ifndef DAY_NIGHT_CYCLE_HPP
#define DAY_NIGHT_CYCLE_HPP

#include "graphics/shader_program.hpp"
#include "models/directional_light_model.hpp"

class DayNightCycle
{
public:
	static void update(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	static void setMoon(DirectionalLightModel& moon);

private:
	static float s_secondsPerDay;
	static float s_timeOfDay;
	static int s_day;
	static DirectionalLightModel* s_moon;

	DayNightCycle() = delete;
	static void updateTimeOfDay();
	static void updateGlobalShading(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	static float getLightCoefficient();
	static float getFogCoefficient();
	~DayNightCycle() = delete;
};

#endif
