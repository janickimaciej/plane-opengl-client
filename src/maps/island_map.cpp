#include "maps/island_map.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/mesh.hpp"
#include "graphics/world_shading.hpp"
#include "maps/map.hpp"
#include "models/directional_light_model.hpp"
#include "models/zeppelin.hpp"

constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
constexpr glm::vec3 sunLight{1, 1, 1};

IslandMap::IslandMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
	AssetManager<const Texture>& textureManager) :
	m_zeppelin{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager},
	m_moon{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager, moonLight},
	m_sun{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager, sunLight},
	m_dayNightCycle{m_moon, m_sun, worldShading, surfaceShaderProgram, lightShaderProgram}
{ }

void IslandMap::setModels()
{
	constexpr float moonRotationPitch = -45;
	m_moon.rotatePitch(moonRotationPitch);

	constexpr float sunRotationPitch = -90;
	m_sun.rotatePitch(sunRotationPitch);

	constexpr glm::vec3 zeppelinPosition{100, 150, -250};
	m_zeppelin.translate(zeppelinPosition);
}

void IslandMap::update(const Map& previousMap)
{
	// TODO: replace with template?
	const IslandMap& previousIslandMap = static_cast<const IslandMap&>(previousMap);
	m_dayNightCycle.updateTime(previousIslandMap.getDayNightCycle());
}

void IslandMap::updateShaders()
{
	m_zeppelin.updateShaders();

	m_dayNightCycle.updateWorldShading();
}

void IslandMap::render() const
{
	m_zeppelin.render();
}

const DayNightCycle& IslandMap::getDayNightCycle() const
{
	return m_dayNightCycle;
}
