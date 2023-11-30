#pragma once

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
		void setOwnInput(int second, unsigned int frame, const Common::UserInput& ownInput);
		void update(int second, unsigned int frame);

	private:
		static constexpr int bufferSize = 100;
		std::array<SimulationBufferElement, bufferSize> m_buffer;
		int m_ownId{};

		void updateUserInputs(int second, unsigned int previousFrame, unsigned int frame);
		void updateScene(unsigned int previousFrame, unsigned int frame,
			std::unordered_map<int, Common::UserInfo> userInfos, bool hasStateFrame);
	};
};
