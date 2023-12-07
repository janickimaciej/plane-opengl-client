#pragma once

#include <string>

namespace Graphics
{
	std::string SH_PATH(const std::string& name);
	std::string SM_PATH(const std::string& name);
	std::string T_PATH(const std::string& name);

	inline const std::string SH_SURFACE_VERTEX = SH_PATH("surfaceVertex");
	inline const std::string SH_SURFACE_FRAGMENT = SH_PATH("surfaceFragment");
	inline const std::string SH_LIGHT_VERTEX = SH_PATH("lightVertex");
	inline const std::string SH_LIGHT_FRAGMENT = SH_PATH("lightFragment");

	inline const std::string SM_AIRPORT_APRON = SM_PATH("airportApron");
	inline const std::string SM_AIRPORT_GROUND = SM_PATH("airportGround");
	inline const std::string SM_AIRPORT_HANGAR = SM_PATH("airportHangar");
	inline const std::string SM_AIRPORT_LIGHT = SM_PATH("airportLight");
	inline const std::string SM_AIRPORT_LIGHT_BODY = SM_PATH("airportLightBody");
	inline const std::string SM_AIRPORT_RUNWAY = SM_PATH("airportRunway");
	inline const std::string SM_AIRPORT_TOWER = SM_PATH("airportTower");
	inline const std::string SM_AIRPLANE_BODY = SM_PATH("airplaneBody");
	inline const std::string SM_AIRPLANE_CAP = SM_PATH("airplaneCap");
	inline const std::string SM_AIRPLANE_JOINS = SM_PATH("airplaneJoins");
	inline const std::string SM_AIRPLANE_LIGHT = SM_PATH("airplaneLight");
	inline const std::string SM_AIRPLANE_PROPELLER = SM_PATH("airplanePropeller");
	inline const std::string SM_AIRPLANE_TIRES = SM_PATH("airplaneTires");
	inline const std::string SM_ZEPPELIN_BODY = SM_PATH("zeppelinBody");

	inline const std::string T_ASPHALT = T_PATH("asphalt");
	inline const std::string T_ASPHALT_BRIGHT = T_PATH("asphaltBright");
	inline const std::string T_CAMO = T_PATH("camo");
	inline const std::string T_CONCRETE = T_PATH("concrete");
	inline const std::string T_GRASS = T_PATH("grass");
	inline const std::string T_TENT = T_PATH("tent");
};
