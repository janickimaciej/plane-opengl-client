#include "graphics/maps/airportMap.hpp"

#include "common/terrains/maps/map.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/dayNightCycle.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/directionalLightModel.hpp"
#include "graphics/models/zeppelin.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	static constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
	static constexpr glm::vec3 sunLight{1, 1, 1};

	AirportMap::AirportMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<std::string, const Texture>& textureManager,
		std::unique_ptr<Common::Terrains::Map> terrain) :
		Map{std::move(terrain)},
		m_airport{surfaceShaderProgram, lightShaderProgram, fileMeshManager, textureManager},
		m_zeppelin{surfaceShaderProgram, fileMeshManager},
		m_moon{surfaceShaderProgram, moonLight},
		m_sun{surfaceShaderProgram, sunLight},
		m_dayNightCycle{m_moon, m_sun, worldShading}
	{
		setModels();
	}

	void AirportMap::update(int day, float timeOfDay)
	{
		m_dayNightCycle.setDay(day);
		m_dayNightCycle.setTimeOfDay(timeOfDay);
		m_dayNightCycle.updateWorldShading();
	}

	void AirportMap::updateShaders()
	{
		m_airport.updateShaders();
		m_zeppelin.updateShaders();
		m_moon.updateShaders();
		m_sun.updateShaders();
	}

	void AirportMap::render() const
	{
		m_airport.render();
		m_zeppelin.render();
	}

	void AirportMap::setModels()
	{
		m_airport.scale(10);

		static constexpr glm::vec3 zeppelinPosition{100, 150, -250};
		m_zeppelin.translate(zeppelinPosition);

		static constexpr float moonRotationPitchDeg = -135;
		m_moon.rotatePitch(glm::radians(moonRotationPitchDeg));

		static constexpr float sunRotationPitchDeg = -135;
		m_sun.rotatePitch(glm::radians(sunRotationPitchDeg));
	}
};
