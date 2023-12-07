#pragma once

#include "common/frame.hpp"

#include <chrono>

namespace Physics
{
	inline constexpr float physicsTimeStep = 1.0f / Common::framesPerSecond;

	class SimulationClock
	{
		using Duration = std::chrono::duration<float>;
		using TimePoint =
			std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<float>>;

	public:
		SimulationClock(const Duration& offset);
		void getTime(int& second, unsigned int& frame) const;

	private:
		Duration m_offset{};
	};
};
