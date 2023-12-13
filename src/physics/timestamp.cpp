#include "physics/timestamp.hpp"

#include "physics/timestep.hpp"

#include <chrono>

namespace Physics
{
	Timestamp::Timestamp(unsigned int second, unsigned int millisecond) :
		second{second},
		millisecond{millisecond}
	{ }

	Timestamp::Timestamp(std::chrono::duration<float> timestamp)
	{
		std::chrono::minutes minutes =
			std::chrono::duration_cast<std::chrono::minutes>(timestamp);
		std::chrono::seconds seconds =
			std::chrono::duration_cast<std::chrono::seconds>(timestamp - minutes);
		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds>(timestamp - minutes -
				seconds);

		second = static_cast<unsigned int>(seconds.count());
		millisecond = static_cast<unsigned int>(milliseconds.count());
	}

	Timestamp Timestamp::systemNow()
	{
		return Timestamp{std::chrono::steady_clock::now().time_since_epoch()};
	}

	Timestamp operator+(const Timestamp& timestamp1, const Timestamp& timestamp2)
	{
		Timestamp result{};
		result.second = timestamp1.second + timestamp2.second;
		result.millisecond = timestamp1.millisecond + timestamp2.millisecond;
		result.normalize();
		return result;
	}

	Timestamp operator-(const Timestamp& timestamp1, const Timestamp& timestamp2)
	{
		Timestamp result{};
		result.second = timestamp1.second - timestamp2.second;
		result.millisecond = timestamp1.millisecond - timestamp2.millisecond;
		result.normalize();
		return result;
	}

	Timestamp operator*(float number, const Timestamp& timestamp)
	{
		Timestamp result{};
		result.second = static_cast<unsigned int>(timestamp.second * number + 0.5f);
		result.millisecond = static_cast<unsigned int>(timestamp.millisecond * number + 0.5f);
		result.normalize();
		return result;
	}

	Timestamp operator/(const Timestamp& timestamp, float number)
	{
		Timestamp result{};
		result.second = static_cast<unsigned int>(timestamp.second / number + 0.5f);
		result.millisecond = static_cast<unsigned int>(timestamp.millisecond / number + 0.5f);
		result.normalize();
		return result;
	}

	void Timestamp::normalize()
	{
		while (millisecond < 0)
		{
			millisecond += millisecondsPerSecond;
			--second;
		}

		while (second < 0)
		{
			second += secondsPerMinute;
		}

		while (millisecond >= millisecondsPerSecond)
		{
			millisecond -= millisecondsPerSecond;
			++second;
		}

		while (second >= secondsPerMinute)
		{
			second -= secondsPerMinute;
		}
	}
};
