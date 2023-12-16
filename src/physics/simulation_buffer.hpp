#pragma once

#include "common/airplane_info.hpp"
#include "physics/player_info.hpp"
#include "physics/player_input.hpp"
#include "physics/simulation_buffer_element.hpp"
#include "physics/simulation_buffer_player.hpp"
#include "physics/timestep.hpp"

#include <array>
#include <unordered_map>

namespace Physics
{
	class SimulationBuffer
	{
	public:
		static constexpr int simulationBufferSize = framesPerSecond;

		SimulationBuffer(int ownId);

		void writeControlFrame(const Timestep& timestep, int playerId,
			const PlayerInput& playerInput);
		void writeStateFrame(const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);

		bool setOwnInput(const Timestep& timestep, const PlayerInput& ownInput);
		void update(const Timestep& timestep);
		std::unordered_map<int, Common::AirplaneInfo> getAirplaneInfos(const Timestep& timestep);

	private:
		std::array<SimulationBufferElement, simulationBufferSize> m_buffer{};
		int m_ownId{};

		void removePlayerInputs(const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);
		void addAndUpdatePlayerInputs(const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos);

		void removePlayerInputs(const Timestep& previousTimestep, const Timestep& timestep);
		void addAndUpdatePlayerInputs(const Timestep& previousTimestep, const Timestep& timestep);
		void updateScene(const Timestep& previousTimestep, const Timestep& timestep,
			const std::unordered_map<int, PlayerInfo>& playerInfos, bool hasStateFrame);
	};
};
