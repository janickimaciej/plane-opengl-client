#include "graphics/scene.hpp"

#include "common/airplane_info.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/cameras/model_camera.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "graphics/world_shading.hpp"

#include <cstddef>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Graphics
{
	Scene::Scene(int ownId, Common::AirplaneTypeName ownAirplaneTypeName, MapName mapName) :
		m_worldShading{m_surfaceShaderProgram, m_lightShaderProgram}
	{
		m_airplanes.insert({ownId, Airplane::createAirplane(m_surfaceShaderProgram,
			m_lightShaderProgram, m_fileMeshManager, m_textureManager, ownAirplaneTypeName)});

		constexpr float FoVDeg = 60;
		constexpr float nearPlane = 1;
		constexpr float farPlane = 10000;
		m_camera = std::make_unique<ModelCamera>(*m_airplanes.at(ownId).get(), glm::radians(FoVDeg),
			nearPlane, farPlane, m_surfaceShaderProgram, m_lightShaderProgram);
		constexpr float cameraPitchDeg = -10;
		m_camera->rotatePitch(glm::radians(cameraPitchDeg));

		switch (ownAirplaneTypeName)
		{
		case Common::AirplaneTypeName::mustang:
			m_camera->translate(glm::vec3{0, 4, 16});
			break;

		case Common::AirplaneTypeName::jw1:
			m_camera->translate(glm::vec3{0, 10, 25});
			break;
		}

		m_map = Map::createMap(mapName, m_worldShading, m_surfaceShaderProgram,
			m_lightShaderProgram, m_fileMeshManager, m_proceduralMeshManager, m_textureManager);
	}

	void Scene::update(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos, int day,
		float timeOfDay)
	{
		m_map->update(day, timeOfDay);
		removeAirplanes(airplaneInfos);
		addAndUpdateAirplanes(airplaneInfos);
		// TODO: update bullets
	}

	void Scene::updateShaders(float aspectRatio)
	{
		m_map->updateShaders();
		for (std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			airplane.second->updateShaders();
		}
		m_camera->updateShaders(aspectRatio);
		m_worldShading.updateShaders();
	}

	void Scene::render() const
	{
		m_map->render();
		for (const std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			airplane.second->render();
		}
		// TODO: render bullets
	}

	void Scene::removeAirplanes(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			if (!airplaneInfos.contains(airplane.first))
			{
				keysToBeDeleted.push_back(airplane.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_airplanes.erase(key);
		}
	}

	void Scene::addAndUpdateAirplanes(
		const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos)
	{
		for (const std::pair<const int, Common::AirplaneInfo>& airplaneInfo : airplaneInfos)
		{
			if (!m_airplanes.contains(airplaneInfo.first))
			{
				m_airplanes.insert({airplaneInfo.first, Airplane::createAirplane
					(
						m_surfaceShaderProgram,
						m_lightShaderProgram,
						m_fileMeshManager,
						m_textureManager,
						airplaneInfo.second.airplaneTypeName
					)});
			}
			m_airplanes.at(airplaneInfo.first)->setState(airplaneInfo.second.state);
			m_airplanes.at(airplaneInfo.first)->setCtrl(airplaneInfo.second.airplaneCtrl);
		}
	}
};
