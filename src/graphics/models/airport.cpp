#include "graphics/models/airport.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>
#include <vector>

namespace Graphics
{
	const std::string modelName = "airport";

	const std::string apronPath = meshPath(modelName, "apron");
	const std::string groundPath = meshPath(modelName, "ground");
	const std::string hangarPath = meshPath(modelName, "hangar");
	const std::string lightPath = meshPath(modelName, "light");
	const std::string lightBodyPath = meshPath(modelName, "lightBody");
	const std::string runwayPath = meshPath(modelName, "runway");
	const std::string towerPath = meshPath(modelName, "tower");
	
	const std::string asphaltPath = texturePath(modelName, "asphalt");
	const std::string asphaltBrightPath = texturePath(modelName, "asphaltBright"); 
	const std::string concretePath = texturePath(modelName, "concrete");
	const std::string grassPath = texturePath(modelName, "grass");
	const std::string tentPath = texturePath(modelName, "tent");

	constexpr std::size_t hangarCount = 3;
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
		m_ground{surfaceShaderProgram, meshManager.get(groundPath), defaultMaterial,
			textureManager.get(grassPath)},
		m_runway{surfaceShaderProgram, meshManager.get(runwayPath), defaultMaterial,
			textureManager.get(asphaltPath)},
		m_apron{surfaceShaderProgram, meshManager.get(apronPath), defaultMaterial,
			textureManager.get(asphaltBrightPath)},
		m_tower{surfaceShaderProgram, meshManager.get(towerPath), concrete,
			textureManager.get(concretePath)},
		m_pointLight{surfaceShaderProgram, glm::vec3{1, 1, 1}, lightsAttenuationQuadratic / 10,
			lightsAttenuationLinear / 10, lightsAttenuationConstant / 10}
	{
		const Submodel hangarSubmodel{surfaceShaderProgram, meshManager.get(hangarPath),
			defaultMaterial, textureManager.get(tentPath)};
		for (std::size_t i = 0; i < hangarCount; ++i)
		{
			m_hangars.push_back(hangarSubmodel);

			constexpr float hangarsGapZ = 46;
			m_hangars[i].translate(glm::vec3{0, 0, -hangarsGapZ * static_cast<int>(i)});
		}

		const Submodel lightBodySubmodel{surfaceShaderProgram,
			meshManager.get(lightBodyPath), metal};
		for (std::size_t i = 0; i < SpotLight::airportLightCount; ++i)
		{
			m_lightBodies.push_back(lightBodySubmodel);
			m_lights.push_back(std::make_unique<SpotLight>(surfaceShaderProgram, lightsColor,
				lightsAttenuationQuadratic, lightsAttenuationLinear, lightsAttenuationConstant,
				glm::radians(lightsCutoffInnerDeg), glm::radians(lightsCutoffOuterDeg)));
			m_lightSubmodels.push_back(LightSubmodel{*m_lights[i], lightShaderProgram,
				meshManager.get(lightPath), yellowLightGlass});

			constexpr float firstLightPositionX = -49;
			constexpr float lightsGapX = 14;
			constexpr float lightsPositionY = 7;
			constexpr float lightsPositionZ = 250;
			glm::vec3 lightPosition{firstLightPositionX + lightsGapX * static_cast<int>(i),
				lightsPositionY, lightsPositionZ};
			m_lightBodies[i].translate(lightPosition);
			m_lights[i]->translate(lightPosition);

			constexpr float lightsRotationYawDeg = 180;
			m_lightBodies[i].rotateYaw(glm::radians(lightsRotationYawDeg));
			m_lights[i]->rotateYaw(glm::radians(lightsRotationYawDeg));

			constexpr float lightsRotationPitchDeg = 15;
			m_lightBodies[i].rotatePitch(glm::radians(lightsRotationPitchDeg));
			m_lights[i]->rotatePitch(glm::radians(lightsRotationPitchDeg));
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
