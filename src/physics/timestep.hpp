#pragma once

namespace Physics
{
	constexpr unsigned int framesPerSecond = 100;
	constexpr unsigned int millisecondsPerSecond = 1000;
	constexpr unsigned int secondsPerMinute = 60;

	struct Timestep
	{
		unsigned int second{};
		unsigned int frame{};

		bool operator==(const Timestep& timestep) const;
		bool operator<(const Timestep& timestep) const;
		bool operator<=(const Timestep& timestep) const;
		Timestep previous() const;
		Timestep next() const;
	};
};
