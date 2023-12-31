#include "graphics/meshes/mesh_generator.hpp"

#include "common/terrains/maps/hills_map.hpp"
#include "graphics/meshes/map_generator.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/meshes/vertex.hpp"

#include <array>
#include <cmath>
#include <functional>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> MeshGenerator::generate(ProceduralMeshName name)
	{
		switch (name)
		{
		case ProceduralMeshName::hills:
			return MapGenerator::generate(Common::Terrains::HillsMap{});
		}
		assert(false);
		return std::vector<Vertex>{};
	}
};
