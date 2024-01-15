#pragma once

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics
{
	class BillboardGenerator
	{
	public:
		static std::vector<Vertex> generate(float width, float height);
	};
};
