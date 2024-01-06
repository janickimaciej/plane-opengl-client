#include "graphics/meshes/bullet_generator.hpp"

#include "common/config.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> BulletGenerator::generate()
	{
		constexpr float tracerLength = Common::tracerLength;
		constexpr float tracerWidth = 0.2f;

		std::vector<Vertex> vertices{};

		addDoubleSidedTriangle(vertices, glm::vec3{0, -tracerWidth / 2, 0},
			glm::vec3{0, tracerWidth / 2, 0}, glm::vec3{0, tracerWidth / 2, tracerLength});
		addDoubleSidedTriangle(vertices, glm::vec3{0, -tracerWidth / 2, 0},
			glm::vec3{0, -tracerWidth / 2, tracerLength},
			glm::vec3{0, tracerWidth / 2, tracerLength});
		addDoubleSidedTriangle(vertices, glm::vec3{-tracerWidth / 2, 0, 0},
			glm::vec3{tracerWidth / 2, 0, 0}, glm::vec3{tracerWidth / 2, 0, tracerLength});
		addDoubleSidedTriangle(vertices, glm::vec3{-tracerWidth / 2, 0, 0},
			glm::vec3{-tracerWidth / 2, 0, tracerLength},
			glm::vec3{tracerWidth / 2, 0, tracerLength});

		return vertices;
	}

	void BulletGenerator::addDoubleSidedTriangle(std::vector<Vertex>& vertices,
		const glm::vec3& vertex1Position, const glm::vec3& vertex2Position,
		const glm::vec3& vertex3Position)
	{
		std::array<Vertex, 3> triangle{};
		triangle[0].position = vertex1Position;
		triangle[1].position = vertex2Position;
		triangle[2].position = vertex3Position;

		vertices.push_back(triangle[0]);
		vertices.push_back(triangle[1]);
		vertices.push_back(triangle[2]);

		vertices.push_back(triangle[2]);
		vertices.push_back(triangle[1]);
		vertices.push_back(triangle[0]);
	}
};
