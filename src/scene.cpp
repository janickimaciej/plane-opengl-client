#include "scene.hpp"

#include "database/airplane_database.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/cameras/model_camera.hpp"
#include "maps/map.hpp"
#include "maps/map_name.hpp"
#include "models/airplane.hpp"
#include "sync/user_info.hpp"

#include <cstddef>
#include <utility>
#include <vector>

Scene::Scene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager) :
	m_worldShading{surfaceShaderProgram, lightShaderProgram},
	m_surfaceShaderProgram{surfaceShaderProgram},
	m_lightShaderProgram{lightShaderProgram},
	m_meshManager{meshManager},
	m_textureManager{textureManager}
{ }

void Scene::updateWithoutStateFrame(const Scene& previousScene,
	const std::unordered_map<int, UserInfo>& userInfos)
{
	removeAirplanesWithoutStateFrame(previousScene);
	addAndUpdateAirplanesWithoutStateFrame(previousScene, userInfos);
	updateBullets(previousScene);
	updateMap(*(previousScene.m_map));
	detectCollisions();
}

void Scene::updateWithStateFrame(const Scene& previousScene,
	const std::unordered_map<int, UserInfo>& users, int ownId, MapName mapName)
{
	removeAirplanesWithStateFrame(users);
	addAndUpdateAirplanesWithStateFrame(users);
	updateBullets(previousScene);
	updateMap(*(previousScene.m_map));
	detectCollisions();
	if (!m_isInitialized)
	{
		initialize(ownId, mapName);
	}
}

void Scene::updateShadersAndRender(float aspectRatio)
{
	updateShaders(aspectRatio);
	render();
}

void Scene::removeAirplanesWithoutStateFrame(const Scene& previousScene)
{
	std::vector<int> keysToBeDeleted;
	for (const std::pair<const int, Airplane>& airplane : m_airplanes)
	{
		if (!previousScene.m_airplanes.contains(airplane.first))
		{
			keysToBeDeleted.push_back(airplane.first);
		}
	}
	for (int key : keysToBeDeleted)
	{
		m_airplanes.erase(key);
	}
}

void Scene::addAndUpdateAirplanesWithoutStateFrame(const Scene& previousScene,
	const std::unordered_map<int, UserInfo>& userInfos)
{
	for (const std::pair<const int, Airplane>& previousAirplane : previousScene.m_airplanes)
	{
		if (!m_airplanes.contains(previousAirplane.first))
		{
			m_airplanes.insert(previousAirplane);
		}
		m_airplanes.at(previousAirplane.first).ctrl(userInfos.at(previousAirplane.first).input);
		m_airplanes.at(previousAirplane.first).update(previousAirplane.second);
	}
}

void Scene::removeAirplanesWithStateFrame(const std::unordered_map<int, UserInfo>& userInfos)
{
	std::vector<int> keysToBeDeleted;
	for (const std::pair<const int, Airplane>& airplane : m_airplanes)
	{
		if (!userInfos.contains(airplane.first))
		{
			keysToBeDeleted.push_back(airplane.first);
		}
	}
	for (int key : keysToBeDeleted)
	{
		m_airplanes.erase(key);
	}
}

void Scene::addAndUpdateAirplanesWithStateFrame(const std::unordered_map<int, UserInfo>& userInfos)
{
	for (const std::pair<const int, UserInfo>& userInfo : userInfos)
	{
		if (!m_airplanes.contains(userInfo.first))
		{
			m_airplanes.insert({userInfo.first, Airplane{m_surfaceShaderProgram,
				m_lightShaderProgram, m_meshManager, m_textureManager,
				airplaneTypes[(std::size_t)userInfo.second.state.airplaneTypeName]}});
		}
		m_airplanes.at(userInfo.first).ctrl(userInfo.second.input);
		m_airplanes.at(userInfo.first).setState(userInfo.second.state.state);
	}
}

void Scene::initialize(int ownId, MapName mapName)
{
	constexpr float FoVDeg = 60;
	constexpr float nearPlane = 0.01f;
	constexpr float farPlane = 1000;
	m_camera = std::make_unique<ModelCamera>(FoVDeg, nearPlane, farPlane,
		m_surfaceShaderProgram, m_lightShaderProgram, m_airplanes.at(ownId));
	constexpr float cameraPitchDeg = -10;
	constexpr glm::vec3 cameraPosition{0, 4, 16};
	m_camera->rotatePitch(cameraPitchDeg);
	m_camera->translate(cameraPosition);

	m_map = Map::createMap(mapName, m_worldShading, m_surfaceShaderProgram, m_lightShaderProgram,
		m_meshManager, m_textureManager);
}

void Scene::updateBullets(const Scene& previousScene)
{
	// TODO (with bullet generation)
}

void Scene::updateMap(const Map& previousMap)
{
	m_map->update(previousMap);
}

void Scene::detectCollisions()
{
	// TODO
}

void Scene::updateShaders(float aspectRatio)
{
	m_camera->updateShaders(aspectRatio);
	m_map->updateShaders();
	for (std::pair<const int, Airplane>& airplane : m_airplanes)
	{
		airplane.second.updateShaders();
	}
}

void Scene::render() const
{
	m_map->render();
	for (const std::pair<const int, Airplane>& airplane : m_airplanes)
	{
		airplane.second.render();
	}
	// TODO: render bullets
}
