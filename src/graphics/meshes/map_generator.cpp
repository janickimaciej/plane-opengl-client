#include "graphics/meshes/map_generator.hpp"

#include "common/terrains/maps/map.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> MapGenerator::generate(const Common::Terrains::Map& terrain)
	{
		float lengthX = terrain.getLengthX();
		float lengthZ = terrain.getLengthZ();
		float spacingX = terrain.getSpacingX();
		float spacingZ = terrain.getSpacingZ();
		int cellCountX = static_cast<int>(lengthX / spacingX) - 1;
		int cellCountZ = static_cast<int>(lengthZ / spacingZ) - 1;

		std::vector<Vertex> vertices{};

		for (int i = 0; i < cellCountX; ++i)
		{
			for (int j = 0; j < cellCountZ; ++j)
			{
				std::array<Vertex, 3> triangle1{};
				std::array<Vertex, 3> triangle2{};

				triangle2[0].position = calcPosition(i * spacingX, j * spacingZ, terrain);
				triangle2[0].texturePosition = glm::vec2{0, 0};
				triangle2[0].normalVector = calcNormalVector(i * spacingX, j * spacingZ, terrain);

				triangle2[1].position = calcPosition(i * spacingX, (j + 1) * spacingZ, terrain);
				triangle2[1].texturePosition = glm::vec2{0, 1};
				triangle2[1].normalVector = calcNormalVector(i * spacingX, (j + 1) * spacingZ,
					terrain);

				triangle2[2].position = calcPosition((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);
				triangle2[2].texturePosition = glm::vec2{1, 1};
				triangle2[2].normalVector = calcNormalVector((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);
				
				vertices.push_back(triangle2[0]);
				vertices.push_back(triangle2[1]);
				vertices.push_back(triangle2[2]);

				triangle1[0].position = calcPosition(i * spacingX, j * spacingZ, terrain);
				triangle1[0].texturePosition = glm::vec2{0, 0};
				triangle1[0].normalVector = calcNormalVector(i * spacingX, j * spacingZ,
					terrain);

				triangle1[1].position = calcPosition((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);
				triangle1[1].texturePosition = glm::vec2{1, 1};
				triangle1[1].normalVector = calcNormalVector((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);

				triangle1[2].position = calcPosition((i + 1) * spacingX, j * spacingZ, terrain);
				triangle1[2].texturePosition = glm::vec2{1, 0};
				triangle1[2].normalVector = calcNormalVector((i + 1) * spacingX, j * spacingZ,
					terrain);

				vertices.push_back(triangle1[0]);
				vertices.push_back(triangle1[1]);
				vertices.push_back(triangle1[2]);
			}
		}

		return vertices;
	}
	
	glm::vec3 MapGenerator::calcPosition(float x, float z, const Common::Terrains::Map& map)
	{
		return glm::vec3{x, map.height(x, z), z};
	}

	glm::vec3 MapGenerator::calcNormalVector(float x, float z, const Common::Terrains::Map& map)
	{
		return glm::normalize(glm::vec3{-map.heightDerivX(x, z), 1, -map.heightDerivZ(x, z)});
	}
};
