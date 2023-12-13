#pragma once

#include "common/airplane_info.hpp"
#include "common/user_info.hpp"
#include "common/user_input.hpp"
#include "physics/simulation_buffer_element.hpp"
#include "physics/simulation_buffer_user.hpp"
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

		void writeControlFrame(const Timestep& timestep, int userId,
			const Common::UserInput& userInput);
		void writeStateFrame(const Timestep& timestep,
			const std::unordered_map<int, Common::UserInfo>& userInfos);

		bool setOwnInput(const Timestep& timestep, const Common::UserInput& ownInput);
		void update(const Timestep& timestep);
		std::unordered_map<int, Common::AirplaneInfo> getAirplaneInfos(const Timestep& timestep);

	private:
		std::array<SimulationBufferElement, simulationBufferSize> m_buffer{};
		int m_ownId{};

		void removeUserInputs(const Timestep& timestep,
			const std::unordered_map<int, Common::UserInfo>& userInfos);
		void addAndUpdateUserInputs(const Timestep& timestep,
			const std::unordered_map<int, Common::UserInfo>& userInfos);

		void removeUserInputs(const Timestep& previousTimestep, const Timestep& timestep);
		void addAndUpdateUserInputs(const Timestep& previousTimestep, const Timestep& timestep);
		void updateScene(const Timestep& previousTimestep, const Timestep& timestep,
			const std::unordered_map<int, Common::UserInfo>& userInfos, bool hasStateFrame);
	};
};
