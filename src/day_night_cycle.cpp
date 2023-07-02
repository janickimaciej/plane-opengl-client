#include "day_night_cycle.hpp"
#include <glm/gtc/constants.hpp>
#include "time.hpp"

constexpr float pi = glm::pi<float>();
constexpr float transitionLength = 0.1f;
constexpr glm::vec3 nightBackgroundColor = glm::vec3(0, 0, 0.1);
constexpr glm::vec3 dayBackgroundColor = glm::vec3(0.6, 0.6, 1);
constexpr float nightAmbient = 0.2f;
constexpr float dayAmbient = 0.7f;
constexpr float lowFogDensity = 0.003f;
constexpr float highFogDensity = 0.01f;
constexpr glm::vec3 sunLight = glm::vec3(1, 1, 1);
constexpr glm::vec3 moonLight = glm::vec3(0.2, 0.2, 0.2);

float DayNightCycle::secondsPerDay = 24*5;
float DayNightCycle::timeOfDay;
int DayNightCycle::day = 0;
DirectionalLightModel* DayNightCycle::moon;

void DayNightCycle::updateTimeOfDay() {
	float deltaTime = Time::getDeltaTime();
	timeOfDay += deltaTime/secondsPerDay;
	while(timeOfDay >= 1) {
		timeOfDay -= 1;
		day++;
	}
}

void DayNightCycle::updateGlobalShading(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) {
	constexpr float fogGradient = 1.5f;

	float lightCoefficient = getLightCoefficient();
	float fogCoefficient = getFogCoefficient();

	GlobalShading::setBackgroundColor(lightCoefficient*dayBackgroundColor +
		(1 - lightCoefficient)*nightBackgroundColor);
	GlobalShading::setAmbient(lightCoefficient*dayAmbient + (1 - lightCoefficient)*nightAmbient);
	GlobalShading::setFogGradient(fogGradient);
	GlobalShading::setFogDensity(fogCoefficient*highFogDensity + (1 - fogCoefficient)*lowFogDensity);
	moon->setLightColor(lightCoefficient*sunLight + (1 - lightCoefficient)*moonLight);
	
	GlobalShading::use(surfaceShaderProgram, lightShaderProgram);
}

float DayNightCycle::getLightCoefficient() {
	if(timeOfDay <= (1 - 2*transitionLength)/4) {
		return 0;
	} else if(timeOfDay <= (1 + 2*transitionLength)/4) {
		return (glm::sin((timeOfDay - 0.25f)/transitionLength*pi) + 1)/2;
	} else if(timeOfDay <= (3 - 2*transitionLength)/4) {
		return 1;
	} else if(timeOfDay <= (3 + 2*transitionLength)/4) {
		return (-glm::sin((timeOfDay - 0.75f)/transitionLength*pi) + 1)/2;
	} else {
		return 0;
	}
}

float DayNightCycle::getFogCoefficient() {
	if(timeOfDay <= (1 - 2*transitionLength)/4) {
		return 0;
	} else if(timeOfDay <= (1 + 2*transitionLength)/4) {
		return (glm::sin((timeOfDay - 0.25f)/transitionLength*pi) + 1)/2;
	} else if(timeOfDay <= (1 + 6*transitionLength)/4) {
		return (-glm::sin((timeOfDay - (0.25f + transitionLength))/transitionLength*pi) + 1)/2;
	} else {
		return 0;
	}
}

void DayNightCycle::update(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) {
	updateTimeOfDay();
	updateGlobalShading(surfaceShaderProgram, lightShaderProgram);
}

void DayNightCycle::setMoon(DirectionalLightModel* moon) {
	DayNightCycle::moon = moon;
}
