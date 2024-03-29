#include "graphics/models/airport.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace Graphics
{
	const std::string modelName = "airport";

	const std::string apronPath = meshPath(modelName, "apron");
	const std::string groundPath = meshPath(modelName, "ground");
	const std::string hangarExteriorPath = meshPath(modelName, "hangarExterior");
	const std::string hangarInteriorPath = meshPath(modelName, "hangarInterior");
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

	const Material ground{glm::vec3{1, 1, 1}, 0.75, 0, 10, false};
	const Material tentExterior{glm::vec3{1, 1, 1}, 0.75, 0, 10, false};
	const Material tentInterior{glm::vec3{0.5, 0.5, 0.5}, 0.75, 0, 10, false};
	const Material concrete{glm::vec3{1, 1, 1}, 0.75, 0, 10, false};
	const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.25, 10, true};
	const Material yellowLightGlass{glm::vec3{1, 1, 0.6}, 1, 1, 1, false};

	Airport::Airport(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_lightShaderProgram{lightShaderProgram},
		m_ground{surfaceShaderProgram, fileMeshManager.get(groundPath), ground,
			textureManager.get(grassPath)},
		m_runway{surfaceShaderProgram, fileMeshManager.get(runwayPath), ground,
			textureManager.get(asphaltPath)},
		m_apron{surfaceShaderProgram, fileMeshManager.get(apronPath), ground,
			textureManager.get(asphaltBrightPath)},
		m_tower{surfaceShaderProgram, fileMeshManager.get(towerPath), concrete,
			textureManager.get(concretePath)}
	{
		const Submodel hangarExteriorSubmodel{surfaceShaderProgram,
			fileMeshManager.get(hangarExteriorPath), tentExterior, textureManager.get(tentPath)};
		const Submodel hangarInteriorSubmodel{surfaceShaderProgram,
			fileMeshManager.get(hangarInteriorPath), tentInterior, textureManager.get(tentPath)};
		for (std::size_t i = 0; i < hangarCount; ++i)
		{
			m_hangarExteriors.push_back(hangarExteriorSubmodel);
			m_hangarInteriors.push_back(hangarInteriorSubmodel);

			constexpr float hangarsGapZ = 46;
			m_hangarExteriors[i].translate(glm::vec3{0, 0, -hangarsGapZ * static_cast<int>(i)});
			m_hangarInteriors[i].translate(glm::vec3{0, 0, -hangarsGapZ * static_cast<int>(i)});
		}

		const Submodel lightBodySubmodel{surfaceShaderProgram,
			fileMeshManager.get(lightBodyPath), metal};
		for (std::size_t i = 0; i < SpotLight::airportLightCount; ++i)
		{
			m_lightBodies.push_back(lightBodySubmodel);
			m_lights.push_back(std::make_unique<SpotLight>(surfaceShaderProgram, lightsColor,
				lightsAttenuationQuadratic, lightsAttenuationLinear, lightsAttenuationConstant,
				glm::radians(lightsCutoffInnerDeg), glm::radians(lightsCutoffOuterDeg)));
			m_lightSubmodels.push_back(LightSubmodel{*m_lights[i], lightShaderProgram,
				fileMeshManager.get(lightPath), yellowLightGlass});

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
	}

	void Airport::updateShaders()
	{
		for (const std::unique_ptr<SpotLight>& light : m_lights)
		{
			light->updateShaders(getMatrix());
		}
	}

	void Airport::render() const
	{
		m_surfaceShaderProgram.use();
		renderSurfaces();

		m_lightShaderProgram.use();
		renderLights();
	}

	void Airport::renderSurfaces() const
	{
		m_ground.render(getMatrix());
		m_runway.render(getMatrix());
		m_apron.render(getMatrix());
		m_tower.render(getMatrix());
		for (const Submodel& hangarExterior : m_hangarExteriors)
		{
			hangarExterior.render(getMatrix());
		}
		for (const Submodel& hangarInterior : m_hangarInteriors)
		{
			hangarInterior.render(getMatrix());
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
