#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "graphics/world_shading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Map
	{
	public:
		virtual void update(int day, float timeOfDay) = 0;
		virtual void updateShaders() = 0;
		virtual void render() const = 0;
		virtual ~Map() = default;

		static std::unique_ptr<Map> createMap(MapName mapName, WorldShading& worldShading,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager);

	protected:
		Map() = default;
	};
};
