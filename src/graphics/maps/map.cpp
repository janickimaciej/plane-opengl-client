#include "graphics/maps/map.hpp"

#include "graphics/maps/airport_map.hpp"
#include "graphics/maps/hills_map.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	std::unique_ptr<Map> Map::createMap(MapName mapName, WorldShading& worldShading,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager)
	{
		switch (mapName)
		{
		case MapName::airport:
			return std::make_unique<AirportMap>(worldShading, surfaceShaderProgram,
				lightShaderProgram, fileMeshManager, textureManager);

		case MapName::hills:
			return std::make_unique<HillsMap>(worldShading, surfaceShaderProgram,
				lightShaderProgram, proceduralMeshManager, textureManager);
		}
		assert(false);
		return nullptr;
	}
};
