#include "graphics/models/airport.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace Graphics
{
	static const std::string modelName = "airport";

	static const std::string apronPath = meshPath(modelName, "apron");
	static const std::string groundPath = meshPath(modelName, "ground");
	static const std::string hangarExteriorPath = meshPath(modelName, "hangarExterior");
	static const std::string hangarInteriorPath = meshPath(modelName, "hangarInterior");
	static const std::string lightPath = meshPath(modelName, "light");
	static const std::string lightBodyPath = meshPath(modelName, "lightBody");
	static const std::string runwayPath = meshPath(modelName, "runway");
	static const std::string towerPath = meshPath(modelName, "tower");
	
	static const std::string asphaltPath = texturePath(modelName, "asphalt");
	static const std::string asphaltBrightPath = texturePath(modelName, "asphaltBright"); 
	static const std::string concretePath = texturePath(modelName, "concrete");
	static const std::string grassPath = texturePath(modelName, "grass");
	static const std::string tentPath = texturePath(modelName, "tent");

	static constexpr std::size_t hangarCount = 3;
	static constexpr float lightsAttenuationQuadratic = 0.0001f;
	static constexpr float lightsAttenuationLinear = 0.0005f;
	static constexpr float lightsAttenuationConstant = 1;
	static constexpr glm::vec3 lightsColor{1, 1, 0.6f};
	static constexpr float lightsCutoffInnerDeg = 25;
	static constexpr float lightsCutoffOuterDeg = 35;

	static const Material ground{glm::vec3{1, 1, 1}, 0.75f, 0, 10, false};
	static const Material tentExterior{glm::vec3{1, 1, 1}, 0.75f, 0, 10, false};
	static const Material tentInterior{glm::vec3{0.5f, 0.5f, 0.5f}, 0.75f, 0, 10, false};
	static const Material concrete{glm::vec3{1, 1, 1}, 0.75f, 0, 10, false};
	static const Material metal{glm::vec3{0.25f, 0.25f, 0.25f}, 0.75f, 0.25f, 10, true};
	static const Material yellowLightGlass{glm::vec3{1, 1, 0.6f}, 1, 1, 1, false};

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

			static constexpr float hangarsGapZ = 46;
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

			static constexpr float firstLightPositionX = -49;
			static constexpr float lightsGapX = 14;
			static constexpr float lightsPositionY = 7;
			static constexpr float lightsPositionZ = 250;
			glm::vec3 lightPosition{firstLightPositionX + lightsGapX * static_cast<int>(i),
				lightsPositionY, lightsPositionZ};
			m_lightBodies[i].translate(lightPosition);
			m_lights[i]->translate(lightPosition);

			static constexpr float lightsRotationYawDeg = 180;
			m_lightBodies[i].rotateYaw(glm::radians(lightsRotationYawDeg));
			m_lights[i]->rotateYaw(glm::radians(lightsRotationYawDeg));

			static constexpr float lightsRotationPitchDeg = 15;
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
