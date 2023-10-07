#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include "graphics/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <string>
#include <string_view>
#include <vector>

class ObjParser
{
public:
	ObjParser() = delete;
	static void parse(const std::string& path, std::vector<Vertex>& vertices);
	~ObjParser() = delete;

private:
	static glm::vec3 parsePosition(const std::string_view line);
	static glm::vec2 parseTexturePosition(const std::string_view line);
	static glm::vec3 parseNormalVector(const std::string_view line);
	static void parseTriangle(const std::string_view line, const std::vector<glm::vec3>& positions,
		const std::vector<glm::vec2>& texturePositions, const std::vector<glm::vec3>& normalVectors,
		std::array<Vertex, 3>& triangle);
};

#endif
