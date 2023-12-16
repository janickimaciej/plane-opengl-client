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

		Timestep previous() const;
		Timestep next() const;
		
		friend Timestep operator-(const Timestep& timestep1, const Timestep& timestep2);

		friend bool operator==(const Timestep& timestep1, const Timestep& timestep2);
		friend bool operator<(const Timestep& timestep1, const Timestep& timestep2);
		friend bool operator<=(const Timestep& timestep1, const Timestep& timestep2);
		friend bool operator>(const Timestep& timestep1, const Timestep& timestep2);

	private:
		static void normalize(int& second, int& frame);
	};
};
