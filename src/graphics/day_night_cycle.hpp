#pragma once

#include "graphics/shader_program.hpp"
#include "graphics/world_shading.hpp"
#include "models/directional_light_model.hpp"

class DayNightCycle
{
public:
	DayNightCycle(DirectionalLightModel& moon, DirectionalLightModel& sun,
		WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	void updateTime(const DayNightCycle& previousDayNightCycle);
	void updateWorldShading();

	float getTimeOfDay() const;
	int getDay() const;

private:
	float m_timeOfDay{};
	int m_day{};
	DirectionalLightModel& m_moon;
	DirectionalLightModel& m_sun;
	WorldShading& m_worldShading;

	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;

	float getLightCoefficient();
	float getFogCoefficient();
};
