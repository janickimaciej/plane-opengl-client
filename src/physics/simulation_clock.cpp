#include "physics/simulation_clock.hpp"

#include "common/frame.hpp"

#include <chrono>

namespace Physics
{
	SimulationClock::SimulationClock(const Duration& offset) :
		m_offset{offset}
	{ }

	void SimulationClock::getTime(int& second, unsigned int& frame) const
	{
		TimePoint currentTime = std::chrono::steady_clock::now();
		Duration simulationTime = (currentTime + m_offset).time_since_epoch();
		std::chrono::minutes minutes =
			std::chrono::duration_cast<std::chrono::minutes>(simulationTime);
		std::chrono::seconds seconds =
			std::chrono::duration_cast<std::chrono::seconds>(simulationTime - minutes);
		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds>(simulationTime - minutes -
				seconds);
		second = static_cast<int>(seconds.count());
		static constexpr float framesPerMillisecond =
			static_cast<float>(Common::framesPerSecond) / 1000;
		frame = static_cast<unsigned int>(milliseconds.count() * framesPerMillisecond);
	}
};
