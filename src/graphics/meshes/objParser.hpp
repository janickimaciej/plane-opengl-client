#pragma once

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <string>
#include <string_view>
#include <vector>

namespace Graphics
{
	class ObjParser
	{
	public:
		ObjParser() = delete;
		static std::vector<Vertex> parse(const std::string& path);
		~ObjParser() = delete;

	private:
		static glm::vec3 parsePosition(const std::string_view line);
		static glm::vec2 parseTexturePosition(const std::string_view line);
		static glm::vec3 parseNormalVector(const std::string_view line);
		static std::array<Vertex, 3> parseTriangle(const std::string_view line,
			const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texturePositions,
			const std::vector<glm::vec3>& normalVectors);
	};
};
