#pragma once

#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <functional>
#include <vector>

namespace Graphics
{
	class MeshGenerator
	{
	public:
		static std::vector<Vertex> generate(ProceduralMeshName name);
	};
};
