#pragma once

#include "common/airplane_info.hpp"
#include "common/airplane_type_name.hpp"
#include "common/bullet_info.hpp"
#include "common/scene_info.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/models/bullet.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "graphics/world_shading.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Graphics
{
	class Scene
	{
	public:
		Scene(int ownId, Common::AirplaneTypeName ownAirplaneTypeName, MapName mapName);
		void update(const Common::SceneInfo& sceneInfo);
		void updateShaders(float aspectRatio);
		void render() const;

	private:
		std::unique_ptr<Map> m_map{};
		std::unordered_map<int, std::unique_ptr<Airplane>> m_airplanes{};
		std::vector<std::unique_ptr<Bullet>> m_bullets{};

		std::unique_ptr<Camera> m_camera{};

		WorldShading m_worldShading;
		
		const ShaderProgram m_surfaceShaderProgram{shaderPath("surfaceVertex"),
			shaderPath("surfaceFragment")};
		const ShaderProgram m_lightShaderProgram{shaderPath("lightVertex"),
			shaderPath("lightFragment")};

		AssetManager<std::string, const Mesh> m_fileMeshManager{};
		AssetManager<ProceduralMeshName, const Mesh> m_proceduralMeshManager{};
		AssetManager<std::string, const Texture> m_textureManager{};

		void removeAirplanes(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void addAndUpdateAirplanes(
			const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void updateBullets(const std::vector<Common::BulletInfo>& bulletInfos);
	};
};
