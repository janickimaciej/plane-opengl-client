#include "graphics/maps/island_map.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/directional_light_model.hpp"
#include "graphics/models/zeppelin.hpp"
#include "graphics/world_shading.hpp"

namespace Graphics
{
	constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
	constexpr glm::vec3 sunLight{1, 1, 1};

	IslandMap::IslandMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
		AssetManager<const Texture>& textureManager) :
		m_airport{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager},
		m_zeppelin{surfaceShaderProgram, lightShaderProgram, meshManager},
		m_moon{surfaceShaderProgram, lightShaderProgram, moonLight},
		m_sun{surfaceShaderProgram, lightShaderProgram, sunLight},
		m_dayNightCycle{m_moon, m_sun, worldShading, surfaceShaderProgram, lightShaderProgram}
	{
		setModels();
	}

	void IslandMap::setModels()
	{
		m_airport.scale(10);

		constexpr glm::vec3 zeppelinPosition{100, 150, -250};
		m_zeppelin.translate(zeppelinPosition);

		constexpr float moonRotationPitch = -45;
		m_moon.rotatePitch(moonRotationPitch);

		constexpr float sunRotationPitch = -90;
		m_sun.rotatePitch(sunRotationPitch);
	}

	void IslandMap::update(int day, float timeOfDay)
	{
		m_dayNightCycle.setDay(day);
		m_dayNightCycle.setTimeOfDay(timeOfDay);
		m_dayNightCycle.updateWorldShading();
	}

	void IslandMap::updateShaders()
	{
		m_airport.updateShaders();
		m_zeppelin.updateShaders();
		m_moon.updateShaders();
		m_sun.updateShaders();
	}

	void IslandMap::render() const
	{
		m_airport.render();
		m_zeppelin.render();
	}

	const DayNightCycle& IslandMap::getDayNightCycle() const
	{
		return m_dayNightCycle;
	}
};
