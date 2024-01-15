#include "graphics/maps/hills_map.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/world_shading.hpp"

#include <string>

namespace Graphics
{
	constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
	constexpr glm::vec3 sunLight{1, 1, 1};

	HillsMap::HillsMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
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
		constexpr float moonRotationPitchDeg = -15;
		constexpr float moonRotationYawDeg = 75;
		m_moon.rotatePitch(glm::radians(moonRotationPitchDeg));
		m_moon.rotateYaw(glm::radians(moonRotationYawDeg));

		constexpr float sunRotationPitchDeg = -15;
		constexpr float sunRotationYawDeg = 75;
		m_sun.rotatePitch(glm::radians(sunRotationPitchDeg));
		m_sun.rotateYaw(glm::radians(sunRotationYawDeg));
	}
};
