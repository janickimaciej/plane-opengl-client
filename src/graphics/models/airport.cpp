#include "graphics/models/airport.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>
#include <vector>

namespace Graphics
{
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
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
		AssetManager<const Texture>& textureManager) :
		Model{surfaceShaderProgram, lightShaderProgram},
		m_ground{surfaceShaderProgram, meshManager.get(SM_AIRPORT_GROUND), defaultMaterial,
			textureManager.get(T_GRASS)},
		m_runway{surfaceShaderProgram, meshManager.get(SM_AIRPORT_RUNWAY), defaultMaterial,
			textureManager.get(T_ASPHALT)},
		m_apron{surfaceShaderProgram, meshManager.get(SM_AIRPORT_APRON), defaultMaterial,
			textureManager.get(T_ASPHALT_BRIGHT)},
		m_tower{surfaceShaderProgram, meshManager.get(SM_AIRPORT_TOWER), concrete,
			textureManager.get(T_CONCRETE)},
		m_pointLight{surfaceShaderProgram, glm::vec3{1, 1, 1}, lightsAttenuationQuadratic / 10,
			lightsAttenuationLinear / 10, lightsAttenuationConstant / 10}
	{
		const Submodel hangarSubmodel{surfaceShaderProgram, meshManager.get(SM_AIRPORT_HANGAR),
			defaultMaterial, textureManager.get(T_TENT)};
		for (std::size_t i = 0; i < hangarsCount; ++i)
		{
			m_hangars.push_back(hangarSubmodel);

			constexpr float hangarsGapZ = 46;
			m_hangars[i].translate(glm::vec3{0, 0, -hangarsGapZ * static_cast<int>(i)});
		}

		const Submodel lightBodySubmodel{surfaceShaderProgram,
			meshManager.get(SM_AIRPORT_LIGHT_BODY), metal};
		const Submodel lightSubmodel{lightShaderProgram, meshManager.get(SM_AIRPORT_LIGHT),
			yellowLightGlass};
		const SpotLight light{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, lightsCutoffInnerDeg,
			lightsCutoffOuterDeg};
		for (std::size_t i = 0; i < lightsCount; ++i)
		{
			m_lightBodies.push_back(lightBodySubmodel);
			m_lights.push_back(std::make_unique<SpotLight>(surfaceShaderProgram, lightsColor,
				lightsAttenuationQuadratic, lightsAttenuationLinear, lightsAttenuationConstant,
				lightsCutoffInnerDeg, lightsCutoffOuterDeg));
			m_lightSubmodels.push_back(LightSubmodel{*m_lights[i], lightShaderProgram,
				meshManager.get(SM_AIRPORT_LIGHT), yellowLightGlass});

			constexpr float firstLightPositionX = -49;
			constexpr float lightsGapX = 14;
			constexpr float lightsPositionY = 7;
			constexpr float lightsPositionZ = 250;
			glm::vec3 lightPosition{firstLightPositionX + lightsGapX * static_cast<int>(i),
				lightsPositionY, lightsPositionZ};
			m_lightBodies[i].translate(lightPosition);
			m_lights[i]->translate(lightPosition);

			constexpr float lightsRotationYaw = 180;
			m_lightBodies[i].rotateYaw(lightsRotationYaw);
			m_lights[i]->rotateYaw(lightsRotationYaw);

			constexpr float lightsRotationPitch = 15;
			m_lightBodies[i].rotatePitch(lightsRotationPitch);
			m_lights[i]->rotatePitch(lightsRotationPitch);
		}

		m_pointLight.translate(glm::vec3{0, 10, 0});
	}

	void Airport::updateShaders()
	{
		for (const std::unique_ptr<SpotLight>& light : m_lights)
		{
			light->updateShaders(getMatrix());
		}
		m_pointLight.updateShaders(getMatrix());
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
		for (const LightSubmodel& lightSubmodel : m_lightSubmodels)
		{
			lightSubmodel.render(getMatrix());
		}
	}
};
