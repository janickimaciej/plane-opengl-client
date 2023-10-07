#include "models/airport.hpp"

#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>
#include <vector>

constexpr std::size_t hangarsCount = 3;
constexpr std::size_t lightsCount = 8;
constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor{1, 1, 0.6};
constexpr float lightsCutoffInnerDeg = 25;
constexpr float lightsCutoffOuterDeg = 35;

// dummy color
const Material defaultMaterial{glm::vec3{1, 0, 0}, 0.75, 0.25, 10};
// dummy color
const Material concrete{glm::vec3{1, 0, 0}, 0.75, 0, 10};
const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.25, 10};
// dummy surface params
const Material yellowLightGlass{glm::vec3{1, 1, 0.6}, 1, 1, 1};

Airport::Airport(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_ground{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPORT_GROUND), defaultMaterial,
		std::make_shared<const Texture>(T_GRASS)},
	m_runway{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPORT_RUNWAY), defaultMaterial,
		std::make_shared<const Texture>(T_ASPHALT)},
	m_apron{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPORT_APRON), defaultMaterial,
		std::make_shared<const Texture>(T_ASPHALT_BRIGHT)},
	m_tower{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPORT_TOWER), concrete,
		std::make_shared<const Texture>(T_CONCRETE)}
{
	const Submodel hangarSubmodel{surfaceShaderProgram,
		std::make_shared<const Mesh>(SM_AIRPORT_HANGAR), defaultMaterial,
		std::make_shared<const Texture>(T_TENT)};
	for (std::size_t i = 0; i < hangarsCount; ++i)
	{
		m_hangars.push_back(hangarSubmodel);

		constexpr float hangarsGapZ = 46;
		m_hangars[i].translate(glm::vec3{0, 0, -hangarsGapZ*(int)i});
	}

	const Submodel lightBodySubmodel{surfaceShaderProgram,
		std::make_shared<const Mesh>(SM_AIRPORT_LIGHT_BODY), metal};
	const Submodel lightSubmodel{lightShaderProgram, std::make_shared<const Mesh>(SM_AIRPORT_LIGHT),
		yellowLightGlass};
	for (std::size_t i = 0; i < lightsCount; ++i)
	{
		m_lightBodies.push_back(Submodel{lightBodySubmodel});
		m_lights.push_back(SpotLight{surfaceShaderProgram, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
			lightsCutoffOuterDeg, getMatrix(), lightSubmodel});

		constexpr float firstLightPositionX = -49;
		constexpr float lightsGapX = 14;
		constexpr float lightsPositionY = 7;
		constexpr float lightsPositionZ = 250;
		glm::vec3 lightPosition{firstLightPositionX + lightsGapX*(int)i, lightsPositionY,
			lightsPositionZ};
		m_lightBodies[i].translate(lightPosition);
		m_lights[i].translate(lightPosition, getMatrix());

		constexpr float lightsRotationYaw = 180;
		m_lightBodies[i].rotateYaw(lightsRotationYaw);
		m_lights[i].yaw(lightsRotationYaw, getMatrix());

		constexpr float lightsRotationPitch = 15;
		m_lightBodies[i].rotatePitch(lightsRotationPitch);
		m_lights[i].pitch(lightsRotationPitch, getMatrix());
	}

	updateShaderLightMatrix();
}

void Airport::updateShaderLightMatrix() const
{
	for (const SpotLight& light : m_lights)
	{
		light.updateShaderLightTranslation(getMatrix());
	}
}

void Airport::renderSurfaces() const
{
	m_ground.render(getMatrix());
	m_runway.render(getMatrix());
	m_apron.render(getMatrix());
	m_tower.render(getMatrix());
	for (const Submodel& hangar : m_hangars)
	{
		hangar.render(getMatrix());
	}
	for (const Submodel& lightBody : m_lightBodies)
	{
		lightBody.render(getMatrix());
	}
}

void Airport::renderLights() const
{
	for (const SpotLight& light : m_lights)
	{
		light.render(getMatrix());
	}
}
