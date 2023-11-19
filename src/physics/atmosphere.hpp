#pragma once

class Atmosphere
{
public:
	static constexpr float seaLevelAirDensity = 1.225f;

	static float airDensity(float height);
};
