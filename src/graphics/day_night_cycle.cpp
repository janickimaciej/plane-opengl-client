#include "graphics/day_night_cycle.hpp"

#include "graphics/global_shading.hpp"
#include "graphics/shader_program.hpp"
#include "models/directional_light_model.hpp"
#include "time.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

constexpr float pi = glm::pi<float>();
constexpr float transitionLength = 0.1f;
constexpr glm::vec3 nightBackgroundColor{0, 0, 0.1};
constexpr glm::vec3 dayBackgroundColor{0.6, 0.6, 1};
constexpr float nightAmbient = 0.2f;
constexpr float dayAmbient = 0.7f;
constexpr float lowFogDensity = 0.003f;
constexpr float highFogDensity = 0.01f;
constexpr glm::vec3 sunLight{1, 1, 1};
constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};

void DayNightCycle::update(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram)
{
	updateTimeOfDay();
	updateGlobalShading(surfaceShaderProgram, lightShaderProgram);
}

void DayNightCycle::setMoon(DirectionalLightModel& moon)
{
	DayNightCycle::s_moon = &moon;
}

float DayNightCycle::s_secondsPerDay = 5 * 24;
float DayNightCycle::s_timeOfDay = 0;
int DayNightCycle::s_day = 0;
DirectionalLightModel* DayNightCycle::s_moon{};

void DayNightCycle::updateTimeOfDay()
{
	float deltaTime = Time::getDeltaTime();
	s_timeOfDay += deltaTime/s_secondsPerDay;
	while (s_timeOfDay >= 1)
	{
		s_timeOfDay -= 1;
		++s_day;
	}
}

void DayNightCycle::updateGlobalShading(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram)
{
	static constexpr float fogGradient = 1.5f;

	float lightCoefficient = getLightCoefficient();
	float fogCoefficient = getFogCoefficient();

	GlobalShading::setBackgroundColor(lightCoefficient * dayBackgroundColor +
		(1 - lightCoefficient) * nightBackgroundColor);
	GlobalShading::setAmbient(lightCoefficient * dayAmbient + (1 - lightCoefficient) *
		nightAmbient);
	GlobalShading::setFogGradient(fogGradient);
	GlobalShading::setFogDensity(fogCoefficient * highFogDensity + (1 - fogCoefficient) *
		lowFogDensity);
	s_moon->setLightColor(lightCoefficient * sunLight + (1 - lightCoefficient) * moonLight);
	
	GlobalShading::use(surfaceShaderProgram, lightShaderProgram);
}

float DayNightCycle::getLightCoefficient()
{
	return 1; //tmp
	/*if (s_timeOfDay <= (1 - 2*transitionLength)/4) //tmpc
	{
		return 0;
	}
	else if (s_timeOfDay <= (1 + 2 * transitionLength) / 4)
	{
		return (glm::sin((s_timeOfDay - 0.25f) / transitionLength * pi) + 1) / 2;
	}
	else if (s_timeOfDay <= (3 - 2 * transitionLength) / 4)
	{
		return 1;
	}
	else if (s_timeOfDay <= (3 + 2 * transitionLength) / 4)
	{
		return (-glm::sin((s_timeOfDay - 0.75f)/transitionLength * pi) + 1) / 2;
	}
	else
	{
		return 0;
	}*/ //tmpc
}

float DayNightCycle::getFogCoefficient()
{
	return 0; //tmp
	/*if (s_timeOfDay <= (1 - 2 * transitionLength) / 4) //tmpc
	{
		return 0;
	}
	else if (s_timeOfDay <= (1 + 2 * transitionLength) / 4)
	{
		return (glm::sin((s_timeOfDay - 0.25f) / transitionLength * pi) + 1) / 2;
	}
	else if (s_timeOfDay <= (1 + 6 * transitionLength) / 4)
	{
		return (-glm::sin((s_timeOfDay - (0.25f + transitionLength)) / transitionLength * pi)
			+ 1) / 2;
	}
	else
	{
		return 0;
	}*/ //tmpc
}
