#pragma once

#include "graphics/cameras/camera.hpp"
#include "graphics/world_shading.hpp"
#include "maps/map.hpp"
#include "maps/map_name.hpp"
#include "models/airplane.hpp"
#include "sync/user_info.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

class Scene
{
public:
	Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
	void updateWithoutStateFrame(const Scene& previousScene,
		const std::unordered_map<int, UserInfo>& userInfos);
	void updateWithStateFrame(const Scene& previousScene,
		const std::unordered_map<int, UserInfo>& userInfos, int ownId, MapName mapName);
	void render(float aspectRatio) const;

private:
	bool m_isInitialized = false;
	
	std::unique_ptr<Map> m_map{};
	std::unordered_map<int, Airplane> m_airplanes{};
	// TODO: m_bullets

	std::unique_ptr<Camera> m_camera{};

	WorldShading m_worldShading;
	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;

	AssetManager<const Mesh>& m_meshManager;
	AssetManager<const Texture>& m_textureManager;

	void removeAirplanesWithoutStateFrame(const Scene& previousScene,
		const std::unordered_map<int, UserInfo>& userInfos);
	void addAndUpdateAirplanesWithoutStateFrame(const Scene& previousScene,
		const std::unordered_map<int, UserInfo>& userInfos);

	void removeAirplanesWithStateFrame(const std::unordered_map<int, UserInfo>& userInfos);
	void addAndUpdateAirplanesWithStateFrame(const std::unordered_map<int, UserInfo>& userInfos);
	void initialize(int ownId, MapName mapName);

	void updateBullets(const Scene& previousScene);
	void updateMap(const Map& previousMap);
	void detectCollisions();
};
