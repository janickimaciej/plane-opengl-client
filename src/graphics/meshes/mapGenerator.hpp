#pragma once

#include "common/terrains/maps/map.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics
{
	class MapGenerator
	{
	public:
		static std::vector<Vertex> generate(const Common::Terrains::Map& map);

	private:
		static glm::vec3 calcPosition(float x, float z, const Common::Terrains::Map& map);
		static glm::vec3 calcNormalVector(float x, float z,
			const Common::Terrains::Map& map);
	};
};
