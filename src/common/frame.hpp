#pragma once

namespace Common
{
	constexpr unsigned int framesPerSecond = 100;
	constexpr int secondsPerMinute = 60;

	void nextFrame(int& second, unsigned int& frame);
	bool earlierThan(int second1, unsigned int frame1, int second2, unsigned int frame2);
};
