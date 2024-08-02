#include "graphics/maps/hillsMap.hpp"

#include "common/terrains/maps/map.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	static constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
	static constexpr glm::vec3 sunLight{1, 1, 1};

	HillsMap::HillsMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager,
		std::unique_ptr<Common::Terrains::Map> terrain) :
		Map{std::move(terrain)},
		m_hills{surfaceShaderProgram, proceduralMeshManager, textureManager},
		m_moon{surfaceShaderProgram, moonLight},
		m_sun{surfaceShaderProgram, sunLight},
		m_dayNightCycle{m_moon, m_sun, worldShading}
	{
		setModels();
	}

	void HillsMap::update(int day, float timeOfDay)
	{
		m_dayNightCycle.setDay(day);
		m_dayNightCycle.setTimeOfDay(timeOfDay);
		m_dayNightCycle.updateWorldShading();
	}

	void HillsMap::updateShaders()
	{
		m_hills.updateShaders();
		m_moon.updateShaders();
		m_sun.updateShaders();
	}

	void HillsMap::render() const
	{
		m_hills.render();
	}
	
	void HillsMap::setModels()
	{
		static constexpr float moonRotationPitchDeg = -15;
		static constexpr float moonRotationYawDeg = 75;
		m_moon.rotatePitch(glm::radians(moonRotationPitchDeg));
		m_moon.rotateYaw(glm::radians(moonRotationYawDeg));

		static constexpr float sunRotationPitchDeg = -15;
		static constexpr float sunRotationYawDeg = 75;
		m_sun.rotatePitch(glm::radians(sunRotationPitchDeg));
		m_sun.rotateYaw(glm::radians(sunRotationYawDeg));
	}
};
