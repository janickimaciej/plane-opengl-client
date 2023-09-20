#ifndef ATMOSPHERE_HPP
#define ATMOSPHERE_HPP

class Atmosphere
{
public:
	static constexpr float seaLevelAirDensity = 1.225;

	static float airDensity(float height);
};

#endif
