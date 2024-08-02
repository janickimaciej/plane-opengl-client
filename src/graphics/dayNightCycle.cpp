#include "graphics/dayNightCycle.hpp"

#include "graphics/shaderProgram.hpp"
#include "graphics/worldShading.hpp"
#include "models/directionalLightModel.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace Graphics
{
	static constexpr float pi = glm::pi<float>();
	static constexpr float transitionLength = 0.1f;

	DayNightCycle::DayNightCycle(DirectionalLightModel& moon, DirectionalLightModel& sun,
		WorldShading& worldShading) :
		m_moon{moon},
		m_sun{sun},
		m_worldShading{worldShading}
	{ }

	void DayNightCycle::setDay(int day)
	{
		m_day = day;
	}

	void DayNightCycle::setTimeOfDay(float timeOfDay)
	{
		m_timeOfDay = timeOfDay;
	}

	void DayNightCycle::updateWorldShading()
	{
		static constexpr glm::vec3 nightBackgroundColor{0, 0, 0.1};
		static constexpr glm::vec3 dayBackgroundColor{0.6, 0.6, 1};
		static constexpr float nightAmbient = 0.1f;
		static constexpr float dayAmbient = 0.5f;
		static constexpr float fogGradient = 2;
		static constexpr float lowFogDensity = 0.0001f;
		static constexpr float highFogDensity = 0.0005f;
		static constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
		static constexpr glm::vec3 sunLight{1, 1, 1};

		float lightCoefficient = getLightCoefficient();
		float fogCoefficient = getFogCoefficient();

		m_worldShading.setBackgroundColor(lightCoefficient * dayBackgroundColor +
			(1 - lightCoefficient) * nightBackgroundColor);
		m_worldShading.setAmbient(lightCoefficient * dayAmbient + (1 - lightCoefficient) *
			nightAmbient);
		m_worldShading.setFogGradient(fogGradient);
		m_worldShading.setFogDensity(fogCoefficient * highFogDensity + (1 - fogCoefficient) *
			lowFogDensity);
		// TODO: fix
		m_moon.setLightColor(lightCoefficient * sunLight + (1 - lightCoefficient) * moonLight);
		// TODO: fix
		m_sun.setLightColor(lightCoefficient * sunLight + (1 - lightCoefficient) * moonLight);
	}

	float DayNightCycle::getLightCoefficient()
	{
		return 0.9f; //tmp
		/*if (m_timeOfDay <= (1 - 2*transitionLength)/4) //tmpc
		{
			return 0;
		}
		else if (m_timeOfDay <= (1 + 2 * transitionLength) / 4)
		{
			return (glm::sin((m_timeOfDay - 0.25f) / transitionLength * pi) + 1) / 2;
		}
		else if (m_timeOfDay <= (3 - 2 * transitionLength) / 4)
		{
			return 1;
		}
		else if (m_timeOfDay <= (3 + 2 * transitionLength) / 4)
		{
			return (-glm::sin((m_timeOfDay - 0.75f) / transitionLength * pi) + 1) / 2;
		}
		else
		{
			return 0;
		}*/ //tmpc
	}

	float DayNightCycle::getFogCoefficient()
	{
		return 0; //tmp
		/*if (m_timeOfDay <= (1 - 2 * transitionLength) / 4) //tmpc
		{
			return 0;
		}
		else if (m_timeOfDay <= (1 + 2 * transitionLength) / 4)
		{
			return (glm::sin((m_timeOfDay - 0.25f) / transitionLength * pi) + 1) / 2;
		}
		else if (m_timeOfDay <= (1 + 6 * transitionLength) / 4)
		{
			return (-glm::sin((m_timeOfDay - (0.25f + transitionLength)) / transitionLength * pi)
				+ 1) / 2;
		}
		else
		{
			return 0;
		}*/ //tmpc
	}
};
