#include "physics/timestep.hpp"

namespace Physics
{
	Timestep Timestep::previous() const
	{
		Timestep previousTimestep{};
		if (frame == 0)
		{
			previousTimestep.frame = framesPerSecond - 1;
			if (second == 0)
			{
				previousTimestep.second = secondsPerMinute - 1;
			}
			else
			{
				previousTimestep.second = second - 1;
			}
		}
		else
		{
			previousTimestep.second = second;
			previousTimestep.frame = frame - 1;
		}
		return previousTimestep;
	}

	Timestep Timestep::next() const
	{
		Timestep nextTimestep{};
		if (frame == framesPerSecond - 1)
		{
			nextTimestep.frame = 0;
			if (second == secondsPerMinute - 1)
			{
				nextTimestep.second = 0;
			}
			else
			{
				nextTimestep.second = second + 1;
			}
		}
		else
		{
			nextTimestep.second = second;
			nextTimestep.frame = frame + 1;
		}
		return nextTimestep;
	}

	Timestep operator-(const Timestep& timestep1, const Timestep& timestep2)
	{
		int second = static_cast<int>(timestep1.second) - static_cast<int>(timestep2.second);
		int frame = static_cast<int>(timestep1.frame) -
			static_cast<int>(timestep2.frame);
		Timestep::normalize(second, frame);
		return Timestep{static_cast<unsigned int>(second), static_cast<unsigned int>(frame)};
	}

	bool operator==(const Timestep& timestep1, const Timestep& timestep2)
	{
		return timestep1.second == timestep2.second && timestep1.frame == timestep2.frame;
	}

	bool operator<(const Timestep& timestep1, const Timestep& timestep2)
	{
		return (timestep1 - timestep2).second >= 30;
	}

	bool operator<=(const Timestep& timestep1, const Timestep& timestep2)
	{
		return timestep1 < timestep2 || timestep1 == timestep2;
	}

	bool operator>(const Timestep& timestep1, const Timestep& timestep2)
	{
		return !(timestep1 <= timestep2);
	}

	void Timestep::normalize(int& second, int& frame)
	{
		while (frame < 0)
		{
			frame += framesPerSecond;
			--second;
		}

		while (second < 0)
		{
			second += secondsPerMinute;
		}

		while (frame >= framesPerSecond)
		{
			frame -= framesPerSecond;
			++second;
		}

		while (second >= secondsPerMinute)
		{
			second -= secondsPerMinute;
		}
	}
};
