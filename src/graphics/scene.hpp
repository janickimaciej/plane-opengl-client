#pragma once

#include "common/airplaneInfo.hpp"
#include "common/airplaneTypeName.hpp"
#include "common/bulletInfo.hpp"
#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/models/bullet.hpp"
#include "graphics/models/hud.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/texture.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Graphics
{
	class Scene
	{
	public:
		Scene(int ownId, Common::AirplaneTypeName ownAirplaneTypeName, Common::MapName mapName);
		void update(const Common::SceneInfo& sceneInfo);
		void updateShaders();
		void render(float aspectRatio) const;

	private:
		int m_ownId{};
		Common::AirplaneTypeName m_ownAirplaneTypeName{};

		const ShaderProgram m_surfaceShaderProgram{shaderPath("surfaceV"),
			shaderPath("surfaceF")};
		const ShaderProgram m_lightShaderProgram{shaderPath("lightV"),
			shaderPath("lightF")};
		const ShaderProgram m_hudShaderProgram{shaderPath("hudV"), shaderPath("hudF")};

		AssetManager<std::string, const Mesh> m_fileMeshManager{};
		AssetManager<ProceduralMeshName, const Mesh> m_proceduralMeshManager{};
		AssetManager<std::string, const Texture> m_textureManager{};

		std::unique_ptr<Map> m_map{};
		std::unordered_map<int, std::unique_ptr<Airplane>> m_airplanes{};
		std::vector<std::unique_ptr<Bullet>> m_bullets{};
		HUD m_hud;

		std::unique_ptr<Camera> m_worldCamera{};
		std::unique_ptr<Camera> m_hudCamera{};

		WorldShading m_worldShading;

		void addAndUpdateAirplanes(
			const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void removeAirplanes(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void updateBullets(const std::vector<Common::BulletInfo>& bulletInfos);
	};
};
