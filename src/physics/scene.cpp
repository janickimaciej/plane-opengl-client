#include "scene.hpp"

#include "physics/airplane_params_database.hpp"
#include "physics/models/airplane.hpp"
#include "physics/player_info.hpp"

#include <cstddef>
#include <unordered_map>
#include <utility>

namespace Physics
{
	void Scene::updateWithoutStateFrame(const Scene& previousScene,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		removeAirplanesWithoutStateFrame(previousScene);
		addAndUpdateAirplanesWithoutStateFrame(previousScene, playerInfos);
		updateCommon(previousScene);
	}

	void Scene::updateWithStateFrame(const Scene& previousScene,
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		removeAirplanesWithStateFrame(playerInfos);
		addAndUpdateAirplanesWithStateFrame(playerInfos);
		updateCommon(previousScene);
	}

	std::unordered_map<int, Common::AirplaneInfo> Scene::getAirplaneInfos() const
	{
		std::unordered_map<int, Common::AirplaneInfo> airplaneInfos;
		for (const std::pair<const int, Airplane>& airplane : m_airplanes)
		{
			airplaneInfos.insert({airplane.first,
				Common::AirplaneInfo
				{
					airplane.second.getState(),
					airplane.second.getCtrl(),
					airplane.second.getAirplaneTypeName()
				}});
		}
		return airplaneInfos;
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
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		for (const std::pair<const int, Airplane>& previousAirplane : previousScene.m_airplanes)
		{
			if (!m_airplanes.contains(previousAirplane.first))
			{
				m_airplanes.insert(previousAirplane);
			}
			m_airplanes.at(previousAirplane.first).setCtrl(
				playerInfos.at(previousAirplane.first).input);
			m_airplanes.at(previousAirplane.first).update(previousAirplane.second);
		}
	}

	void Scene::removeAirplanesWithStateFrame(
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		std::vector<int> keysToBeDeleted{};
		for (const std::pair<const int, Airplane>& airplane : m_airplanes)
		{
			if (!playerInfos.contains(airplane.first))
			{
				keysToBeDeleted.push_back(airplane.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_airplanes.erase(key);
		}
	}

	void Scene::addAndUpdateAirplanesWithStateFrame(
		const std::unordered_map<int, PlayerInfo>& playerInfos)
	{
		for (const std::pair<const int, PlayerInfo>& playerInfo : playerInfos)
		{
			if (!m_airplanes.contains(playerInfo.first))
			{
				m_airplanes.insert({playerInfo.first,
					Airplane{playerInfo.second.state.airplaneTypeName}});
			}
			m_airplanes.at(playerInfo.first).setCtrl(playerInfo.second.input);
			m_airplanes.at(playerInfo.first).setState(playerInfo.second.state.state);
		}
	}

	void Scene::updateCommon(const Scene& previousScene)
	{
		updateBullets();
		detectCollisions();
		m_dayNightCycle.updateTime(previousScene.m_dayNightCycle);
	}

	void Scene::updateBullets(/*const Scene& previousScene*/)
	{
		// TODO (with bullet generation)
	}

	void Scene::detectCollisions()
	{
		// TODO
	}
};
