#pragma once

#include "graphics/meshes/vertex.hpp"

#include <vector>

namespace Graphics
{
	class BulletGenerator
	{
	public:
		static std::vector<Vertex> generate();
	};
};
