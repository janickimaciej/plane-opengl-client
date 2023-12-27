#pragma once

#include <string>

namespace Graphics
{
	std::string shaderPath(const std::string& name);
	std::string meshPath(const std::string& modelName, const std::string& submodelName);
	std::string texturePath(const std::string& modelName, const std::string& submodelName);
};
