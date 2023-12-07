#include "common/frame.hpp"

namespace Common
{
	void nextFrame(int& second, unsigned int& frame)
	{
		if (frame == framesPerSecond - 1)
		{
			frame = 0;
			if (second == secondsPerMinute - 1)
			{
				second = 0;
			}
			else
			{
				++second;
			}
		}
		else
		{
			++frame;
		}
	}

	bool earlierThan(int second1, unsigned int frame1, int second2, unsigned int frame2)
	{
		if ((second1 == secondsPerMinute - 1 || second1 == secondsPerMinute - 2) &&
			(second2 == 0 || second2 == 1))
		{
			return true;
		}
		else if ((second1 == 0 || second1 == 1) &&
			(second2 == secondsPerMinute - 1 || second2 == secondsPerMinute - 2))
		{
			return false;
		}
		else if (second1 < second2 || (second1 == second2 && frame1 < frame2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
