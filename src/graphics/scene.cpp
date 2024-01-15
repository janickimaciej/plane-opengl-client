#include "graphics/scene.hpp"

#include "common/airplane_info.hpp"
#include "common/airplane_type_name.hpp"
#include "common/bullet_info.hpp"
#include "common/map_name.hpp"
#include "common/scene_info.hpp"
#include "graphics/airplane_camera_positions.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/cameras/model_camera.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "graphics/time.hpp"
#include "graphics/world_shading.hpp"

#include <cstddef>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Graphics
{
	constexpr float FoVDeg = 60;
	constexpr float nearPlane = 4;
	constexpr float farPlane = 20000;

	Scene::Scene(int ownId, Common::AirplaneTypeName ownAirplaneTypeName, Common::MapName mapName) :
		m_ownId{ownId},
		m_ownAirplaneTypeName{ownAirplaneTypeName},
		m_worldShading{m_surfaceShaderProgram, m_lightShaderProgram},
		m_hud{m_hudShaderProgram, m_proceduralMeshManager, m_textureManager,
			airplaneCameraPositions[Common::toSizeT(ownAirplaneTypeName)] +
			glm::vec3{0, 0, -nearPlane - 1}}
	{
		m_airplanes.insert({ownId, Airplane::createAirplane(m_surfaceShaderProgram,
			m_lightShaderProgram, m_fileMeshManager, m_textureManager, ownAirplaneTypeName)});

		m_camera = std::make_unique<ModelCamera>(*m_airplanes.at(ownId), glm::radians(FoVDeg),
			nearPlane, farPlane, m_surfaceShaderProgram, m_lightShaderProgram, m_hudShaderProgram);
		constexpr float cameraPitchDeg = -10;
		m_camera->rotatePitch(glm::radians(cameraPitchDeg));
		
		m_camera->translate(airplaneCameraPositions[Common::toSizeT(ownAirplaneTypeName)]);

		m_map = Map::createMap(mapName, m_worldShading, m_surfaceShaderProgram,
			m_lightShaderProgram, m_fileMeshManager, m_proceduralMeshManager, m_textureManager);
	}

	void Scene::update(const Common::SceneInfo& sceneInfo)
	{
		m_lastHUDUpdateTime += Time::getDeltaTime();
		m_map->update(sceneInfo.day, sceneInfo.timeOfDay);
		addAndUpdateAirplanes(sceneInfo.airplaneInfos);
		removeAirplanes(sceneInfo.airplaneInfos);
		updateBullets(sceneInfo.bulletInfos);
		m_hud.setState(m_airplanes[m_ownId]->getState());
		if (m_lastHUDUpdateTime >= 1)
		{
			Common::State ownAirplaneState = m_airplanes[m_ownId]->getState();
			m_hud.update(static_cast<int>(glm::length(3.6f * ownAirplaneState.velocity)),
				static_cast<int>(ownAirplaneState.position.y), m_airplanes[m_ownId]->getHP());
			m_lastHUDUpdateTime = 0;
		}
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
		m_hud.updateShaders();
	}

	void Scene::render() const
	{
		m_map->render();
		for (const std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			airplane.second->render();
		}
		for (const std::unique_ptr<Bullet>& bullet : m_bullets)
		{
			bullet->render();
		}
		m_hud.render();
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
			m_airplanes.at(airplaneInfo.first)->setHP(airplaneInfo.second.hp);
		}
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

	void Scene::updateBullets(const std::vector<Common::BulletInfo>& bulletInfos)
	{
		int sizeDiff = static_cast<int>(m_bullets.size()) - static_cast<int>(bulletInfos.size());
		if (m_bullets.size() > bulletInfos.size())
		{
			m_bullets.erase(m_bullets.end() - sizeDiff, m_bullets.end());
		}

		for (std::size_t i = m_bullets.size(); i < bulletInfos.size(); ++i)
		{
			m_bullets.push_back(std::make_unique<Bullet>(m_lightShaderProgram,
				m_proceduralMeshManager));
		}

		for (std::size_t i = 0; i < bulletInfos.size(); ++i)
		{
			m_bullets.at(i)->setState(bulletInfos.at(i).state);
		}
	}
};
