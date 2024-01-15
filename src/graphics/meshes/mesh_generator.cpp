#include "graphics/meshes/mesh_generator.hpp"

#include "common/terrains/maps/hills_map.hpp"
#include "graphics/config.hpp"
#include "graphics/meshes/billboard_generator.hpp"
#include "graphics/meshes/bullet_generator.hpp"
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
		case ProceduralMeshName::characterBillboard:
		{
			return BillboardGenerator::generate(characterWidth, characterHeight);
		}

		case ProceduralMeshName::bullet:
			return BulletGenerator::generate();

		case ProceduralMeshName::hills:
			return MapGenerator::generate(Common::Terrains::HillsMap{});
		}
		return std::vector<Vertex>{};
	}
};
