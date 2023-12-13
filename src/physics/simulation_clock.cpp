#include "physics/simulation_clock.hpp"

#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <chrono>

namespace Physics
{
	Timestep SimulationClock::getTime() const
	{
		Physics::Timestamp offset = m_offset.load();
		std::chrono::duration<float> simulationTime =
			std::chrono::steady_clock::now().time_since_epoch() -
			std::chrono::seconds(offset.second) - std::chrono::milliseconds(offset.millisecond);

		std::chrono::minutes minutes =
			std::chrono::duration_cast<std::chrono::minutes>(simulationTime);
		std::chrono::seconds seconds =
			std::chrono::duration_cast<std::chrono::seconds>(simulationTime - minutes);
		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds>(simulationTime - minutes -
				seconds);

		static constexpr float framesPerMillisecond = static_cast<float>(framesPerSecond) /
			millisecondsPerSecond;
		return Timestep
			{
				static_cast<unsigned int>(seconds.count()),
				static_cast<unsigned int>(milliseconds.count() * framesPerMillisecond)
			};
	}

	void SimulationClock::initializeOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		m_offset.store(calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp));
	}

	void SimulationClock::updateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp)
	{
		constexpr float newOffsetWeight = 0.02f;
		constexpr float oldOffsetWeight = 1 - newOffsetWeight;
		m_offset = oldOffsetWeight * m_offset.load() + newOffsetWeight *
			calculateOffset(sendTimestamp, receiveTimestamp, serverTimestamp);
	}

	Timestamp SimulationClock::calculateOffset(const Timestamp& sendTimestamp,
		const Timestamp& receiveTimestamp, const Timestamp& serverTimestamp) const
	{
		Timestamp latency = (receiveTimestamp - sendTimestamp) / 2;
		return receiveTimestamp - (serverTimestamp + latency);
	}
};
