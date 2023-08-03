#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include "structs/vertex.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

class ObjParser
{
public:
	ObjParser() = delete;
	static void parse(const std::string& filename, std::vector<Vertex>& vertices);
	~ObjParser() = delete;

private:
	static glm::vec3 parsePosition(const std::string& line);
	static glm::vec2 parseTexturePosition(const std::string& line);
	static glm::vec3 parseNormalVector(const std::string& line);
	static void parseTriangle(const std::string& line, const std::vector<glm::vec3>& positions,
		const std::vector<glm::vec2>& texturePositions, const std::vector<glm::vec3>& normalVectors,
		Vertex triangle[]);
};

#endif
