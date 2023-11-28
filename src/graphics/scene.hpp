#pragma once

#include "common/airplane_type_name.hpp"
#include "common/state.hpp"
#include "common/sync/airplane_info.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/world_shading.hpp"
#include "maps/map.hpp"
#include "maps/map_name.hpp"
#include "models/airplane.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace Graphics
{
	class Scene
	{
	public:
		Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager,
			int ownId, Common::AirplaneTypeName ownAirplaneTypeName, MapName mapName);
		void update(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos,
			/*TODO: bullets*/int day, float timeOfDay);
		void updateShaders(float aspectRatio);
		void render() const;

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

		void removeAirplanes(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void addAndUpdateAirplanes(
			const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
	};
};
