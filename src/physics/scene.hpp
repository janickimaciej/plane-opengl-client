#pragma once

#include "common/airplane_info.hpp"
#include "physics/day_night_cycle.hpp"
#include "physics/models/airplane.hpp"
#include "physics/player_info.hpp"

#include <unordered_map>

namespace Physics
{
	class Scene
	{
	public:
		void updateWithoutStateFrame(const Scene& previousScene,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void updateWithStateFrame(const Scene& previousScene,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		std::unordered_map<int, Common::AirplaneInfo> getAirplaneInfos() const;

	private:
		std::unordered_map<int, Airplane> m_airplanes{};
		// TODO: m_bullets

		DayNightCycle m_dayNightCycle{};

		void removeAirplanesWithoutStateFrame(const Scene& previousScene);
		void addAndUpdateAirplanesWithoutStateFrame(const Scene& previousScene,
			const std::unordered_map<int, PlayerInfo>& playerInfos);

		void removeAirplanesWithStateFrame(
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void addAndUpdateAirplanesWithStateFrame(
			const std::unordered_map<int, PlayerInfo>& playerInfos);

		void updateCommon(const Scene& previousScene);

		void updateBullets(/*const Scene& previousScene*/);
		void detectCollisions();
	};
};
