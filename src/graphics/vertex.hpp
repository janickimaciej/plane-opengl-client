#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	struct Vertex
	{
		glm::vec3 position{};
		glm::vec2 texturePosition{};
		glm::vec3 normalVector{};
	};
};
