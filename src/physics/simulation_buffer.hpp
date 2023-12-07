#pragma once

#include "common/frame.hpp"
#include "common/sync/airplane_info.hpp"
#include "common/sync/user_info.hpp"
#include "common/sync/user_input.hpp"
#include "physics/simulation_buffer_element.hpp"

#include <array>
#include <unordered_map>

namespace Physics
{
	class SimulationBuffer
	{
	public:
		static constexpr int simulationBufferSize = Common::framesPerSecond;

		SimulationBuffer(int ownId);

		void writeControlFrame(int second, unsigned int frame, int id,
			const Common::UserInput& input);
		void writeStateFrame(unsigned int frame,
			const std::unordered_map<int, Common::UserInfo>& userInfos);

		void setOwnInput(int second, unsigned int frame, const Common::UserInput& ownInput);
		void update(int second, unsigned int frame);
		std::unordered_map<int, Common::AirplaneInfo> getAirplaneInfos(unsigned int frame);

	private:
		std::array<SimulationBufferElement, simulationBufferSize> m_buffer{};
		int m_ownId{};

		void removeUserInputs(unsigned int frame,
			const std::unordered_map<int, Common::UserInfo>& userInfos);
		void addAndUpdateUserInputs(unsigned int frame,
			const std::unordered_map<int, Common::UserInfo>& userInfos);

		void removeUserInputs(unsigned int previousFrame, unsigned int frame);
		void addAndUpdateUserInputs(int second, unsigned int previousFrame, unsigned int frame);
		void updateScene(unsigned int previousFrame, unsigned int frame,
			const std::unordered_map<int, Common::UserInfo>& userInfos, bool hasStateFrame);
	};
};
