#include "graphics/meshes/bullet_generator.hpp"

#include "common/config.hpp"
#include "graphics/meshes/vertex.hpp"

#include <array>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> BulletGenerator::generate()
	{
		constexpr float tracerLength = Common::tracerLength;
		constexpr float tracerWidth = 0.2f;

		std::vector<Vertex> vertices{};

		std::array<Vertex, 3> triangle1{};
		triangle1[0].position = glm::vec3{0, -tracerWidth / 2, 0};
		vertices.push_back(triangle1[0]);
		triangle1[1].position = glm::vec3{0, tracerWidth / 2, 0};
		vertices.push_back(triangle1[1]);
		triangle1[2].position = glm::vec3{0, tracerWidth / 2, tracerLength};
		vertices.push_back(triangle1[2]);

		std::array<Vertex, 3> triangle2{};
		triangle2[0].position = glm::vec3{0, -tracerWidth / 2, 0};
		vertices.push_back(triangle2[0]);
		triangle2[1].position = glm::vec3{0, -tracerWidth / 2, tracerLength};
		vertices.push_back(triangle2[1]);
		triangle2[2].position = glm::vec3{0, tracerWidth / 2, tracerLength};
		vertices.push_back(triangle2[2]);

		std::array<Vertex, 3> triangle3{};
		triangle3[0].position = glm::vec3{-tracerWidth / 2, 0, 0};
		vertices.push_back(triangle3[0]);
		triangle3[1].position = glm::vec3{tracerWidth / 2, 0, 0};
		vertices.push_back(triangle3[1]);
		triangle3[2].position = glm::vec3{tracerWidth / 2, 0, tracerLength};
		vertices.push_back(triangle3[2]);

		std::array<Vertex, 3> triangle4{};
		triangle4[0].position = glm::vec3{-tracerWidth / 2, 0, 0};
		vertices.push_back(triangle4[0]);
		triangle4[1].position = glm::vec3{-tracerWidth / 2, 0, tracerLength};
		vertices.push_back(triangle4[1]);
		triangle4[2].position = glm::vec3{tracerWidth / 2, 0, tracerLength};
		vertices.push_back(triangle4[2]);

		return vertices;
	}
};
