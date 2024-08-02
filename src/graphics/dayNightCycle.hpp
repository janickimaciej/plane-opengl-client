#pragma once

#include "graphics/shaderProgram.hpp"
#include "graphics/worldShading.hpp"
#include "models/directionalLightModel.hpp"

namespace Graphics
{
	class DayNightCycle
	{
	public:
		DayNightCycle(DirectionalLightModel& moon, DirectionalLightModel& sun,
			WorldShading& worldShading);
		void updateWorldShading();
		
		void setDay(int day);
		void setTimeOfDay(float timeOfDay);

	private:
		int m_day{};
		float m_timeOfDay{};
		DirectionalLightModel& m_moon;
		DirectionalLightModel& m_sun;
		WorldShading& m_worldShading;

		float getLightCoefficient();
		float getFogCoefficient();
	};
};
