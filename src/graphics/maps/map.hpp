#pragma once

#include "common/mapName.hpp"
#include "common/terrains/maps/map.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/texture.hpp"
#include "graphics/worldShading.hpp"

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
		float getHeight(float x, float z) const;
		virtual ~Map() = default;

		static std::unique_ptr<Map> createMap(Common::MapName mapName, WorldShading& worldShading,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager);

	protected:
		const std::unique_ptr<Common::Terrains::Map> m_terrain{};

		Map(std::unique_ptr<Common::Terrains::Map> terrain);
	};
};
