#include "graphics/meshes/meshGenerator.hpp"

#include "common/terrains/maps/hillsMap.hpp"
#include "graphics/config.hpp"
#include "graphics/meshes/billboardGenerator.hpp"
#include "graphics/meshes/bulletGenerator.hpp"
#include "graphics/meshes/mapGenerator.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
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
