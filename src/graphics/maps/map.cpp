#include "graphics/maps/map.hpp"

#include "common/map_name.hpp"
#include "common/terrains/maps/airport_map.hpp"
#include "common/terrains/maps/hills_map.hpp"
#include "common/terrains/maps/map.hpp"
#include "graphics/maps/airport_map.hpp"
#include "graphics/maps/hills_map.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	std::unique_ptr<Map> Map::createMap(Common::MapName mapName, WorldShading& worldShading,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager)
	{
		switch (mapName)
		{
		case Common::MapName::airport:
			return std::make_unique<AirportMap>(worldShading, surfaceShaderProgram,
				lightShaderProgram, fileMeshManager, textureManager,
				std::make_unique<Common::Terrains::AirportMap>());

		case Common::MapName::hills:
			return std::make_unique<HillsMap>(worldShading, surfaceShaderProgram,
				proceduralMeshManager, textureManager,
				std::make_unique<Common::Terrains::HillsMap>());
		}
		assert(false);
		return nullptr;
	}

	float Map::getHeight(float x, float z) const
	{
		return m_terrain->height(x, z);
	}

	Map::Map(std::unique_ptr<Common::Terrains::Map> terrain) :
		m_terrain{std::move(terrain)}
	{ }
};
