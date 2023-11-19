#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "graphics/world_shading.hpp"
#include "maps/map_name.hpp"

#include <memory>

class Map
{
public:
	virtual void update(const Map& map) = 0;
	virtual void render() const = 0;

	static std::unique_ptr<Map> createMap(MapName mapName, WorldShading& worldShading,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
};
