#include "graphics/paths.hpp"

#include <string>

namespace
{
	std::string SH_PATH(const std::string& name);
	std::string SM_PATH(const std::string& name);
	std::string T_PATH(const std::string& name);
}

const std::string SH_SURFACE_VERTEX = SH_PATH("surfaceVertex");
const std::string SH_SURFACE_FRAGMENT = SH_PATH("surfaceFragment");
const std::string SH_LIGHT_VERTEX = SH_PATH("lightVertex");
const std::string SH_LIGHT_FRAGMENT = SH_PATH("lightFragment");

const std::string SM_AIRPORT_APRON = SM_PATH("airportApron");
const std::string SM_AIRPORT_GROUND = SM_PATH("airportGround");
const std::string SM_AIRPORT_HANGAR = SM_PATH("airportHangar");
const std::string SM_AIRPORT_LIGHT = SM_PATH("airportLight");
const std::string SM_AIRPORT_LIGHT_BODY = SM_PATH("airportLightBody");
const std::string SM_AIRPORT_RUNWAY = SM_PATH("airportRunway");
const std::string SM_AIRPORT_TOWER = SM_PATH("airportTower");
const std::string SM_AIRPLANE_BODY = SM_PATH("airplaneBody");
const std::string SM_AIRPLANE_CAP = SM_PATH("airplaneCap");
const std::string SM_AIRPLANE_JOINS = SM_PATH("airplaneJoins");
const std::string SM_AIRPLANE_LIGHT = SM_PATH("airplaneLight");
const std::string SM_AIRPLANE_PROPELLER = SM_PATH("airplanePropeller");
const std::string SM_AIRPLANE_TIRES = SM_PATH("airplaneTires");
const std::string SM_ZEPPELIN_BODY = SM_PATH("zeppelinBody");

const std::string T_ASPHALT = T_PATH("asphalt");
const std::string T_ASPHALT_BRIGHT = T_PATH("asphaltBright");
const std::string T_CAMO = T_PATH("camo");
const std::string T_CONCRETE = T_PATH("concrete");
const std::string T_GRASS = T_PATH("grass");
const std::string T_TENT = T_PATH("tent");

namespace
{
	std::string SH_PATH(const std::string& name)
	{
		const std::string SH_PREFIX = "src/graphics/shaders/";
		const std::string SH_SUFFIX = "Shader.glsl";
		return SH_PREFIX + name + SH_SUFFIX;
	}

	std::string SM_PATH(const std::string& name)
	{
		const std::string SM_PREFIX = "res/meshes/";
		const std::string SM_SUFFIX = ".obj";
		return SM_PREFIX + name + SM_SUFFIX;
	}

	std::string T_PATH(const std::string& name)
	{
		const std::string T_PREFIX = "res/textures/";
		const std::string T_SUFFIX = ".png";
		return T_PREFIX + name + T_SUFFIX;
	}
}
