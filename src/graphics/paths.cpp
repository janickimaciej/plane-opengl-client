#include "graphics/paths.hpp"

namespace Graphics
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
};
