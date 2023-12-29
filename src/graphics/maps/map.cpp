#include "graphics/maps/map.hpp"

#include "graphics/maps/airport_map.hpp"
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
		case MapName::airport:
			return std::make_unique<AirportMap>(worldShading, surfaceShaderProgram,
				lightShaderProgram, meshManager, textureManager);
		}
		return nullptr;
	}
};
