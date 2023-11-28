#include "graphics/maps/map.hpp"

#include "graphics/maps/island_map.hpp"
#include "graphics/maps/map_name.hpp"

#include <memory>

namespace Graphics
{
	std::unique_ptr<Map> Map::createMap(MapName mapName, WorldShading& worldShading,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager)
	{
		switch (mapName)
		{
		case MapName::island:
			return std::make_unique<IslandMap>(worldShading, surfaceShaderProgram,
				lightShaderProgram, meshManager, textureManager);
		}
		return nullptr;
	}
};
