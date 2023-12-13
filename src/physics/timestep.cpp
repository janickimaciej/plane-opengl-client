#include "physics/timestep.hpp"

namespace Physics
{
	bool Timestep::operator==(const Timestep& timestep) const
	{
		return second == timestep.second && frame == timestep.frame;
	}

	bool Timestep::operator<(const Timestep& timestep) const
	{
		if ((second == secondsPerMinute - 1 || second == secondsPerMinute - 2) &&
			(timestep.second == 0 || timestep.second == 1))
		{
			return true;
		}
		else if ((second == 0 || second == 1) &&
			(timestep.second == secondsPerMinute - 1 || timestep.second == secondsPerMinute - 2))
		{
			return false;
		}
		else if (second < timestep.second ||
			(second == timestep.second && frame < timestep.frame))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Timestep::operator<=(const Timestep& timestep) const
	{
		return *this < timestep || *this == timestep;
	}

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
};
