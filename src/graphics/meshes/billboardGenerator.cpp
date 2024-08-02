#include "graphics/meshes/billboardGenerator.hpp"

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> BillboardGenerator::generate(float width, float height)
	{
		std::vector<Vertex> vertices{};

		std::array<Vertex, 3> triangle1{};
		triangle1[0].position = glm::vec3{0, 0, 0};
		triangle1[0].texturePosition = glm::vec2{0, 0};
		triangle1[1].position = glm::vec3{0, -height, 0};
		triangle1[1].texturePosition = glm::vec2{0, 1};
		triangle1[2].position = glm::vec3{width, -height, 0};
		triangle1[2].texturePosition = glm::vec2{1, 1};

		vertices.push_back(triangle1[0]);
		vertices.push_back(triangle1[1]);
		vertices.push_back(triangle1[2]);

		std::array<Vertex, 3> triangle2{};
		triangle2[0].position = glm::vec3{0, 0, 0};
		triangle2[0].texturePosition = glm::vec2{0, 0};
		triangle2[1].position = glm::vec3{width, -height, 0};
		triangle2[1].texturePosition = glm::vec2{1, 1};
		triangle2[2].position = glm::vec3{width, 0, 0};
		triangle2[2].texturePosition = glm::vec2{1, 0};

		vertices.push_back(triangle2[0]);
		vertices.push_back(triangle2[1]);
		vertices.push_back(triangle2[2]);

		return vertices;
	}
};
