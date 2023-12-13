#pragma once

#include "physics/timestamp.hpp"
#include "physics/timestep.hpp"

#include <atomic>
#include <chrono>

namespace Physics
{
	inline constexpr float physicsTimeStep = 1.0f / framesPerSecond;

	class SimulationClock
	{
	public:
		Timestep getTime() const;
		void initializeOffset(const Timestamp& sendTimestamp, const Timestamp& receiveTimestamp,
			const Timestamp& serverTimestamp);
		void updateOffset(const Timestamp& sendTimestamp, const Timestamp& receiveTimestamp,
			const Timestamp& serverTimestamp);

	private:
		std::atomic<Timestamp> m_offset{};

		Timestamp calculateOffset(const Timestamp& sendTimestamp, const Timestamp& receiveTimestamp,
			const Timestamp& serverTimestamp) const;
	};
};
