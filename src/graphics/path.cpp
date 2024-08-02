#include "graphics/path.hpp"

namespace Graphics
{
	std::string shaderPath(const std::string& name)
	{
		static const std::string prefix = "src/graphics/shaders/";
		static const std::string suffix = "S.glsl";
		return prefix + name + suffix;
	}

	std::string meshPath(const std::string& modelName, const std::string& submodelName)
	{
		static const std::string prefix = "res/meshes/";
		static const std::string suffix = ".obj";
		return prefix + modelName + "/" + submodelName + suffix;
	}

	std::string texturePath(const std::string& modelName, const std::string& submodelName)
	{
		static const std::string prefix = "res/textures/";
		static const std::string suffix = ".png";
		return prefix + modelName + "/" + submodelName + suffix;
	}
};
