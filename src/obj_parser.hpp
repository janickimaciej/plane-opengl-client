#ifndef OBJ_PARSER
#define OBJ_PARSER

#include <string>
#include <vector>
#include "structs/vertex.hpp"

class ObjParser {
	ObjParser() { };
	static glm::vec3 parsePosition(std::string line);
	static glm::vec2 parseTexturePosition(std::string line);
	static glm::vec3 parseNormalVector(std::string line);
	static void parseTriangle(std::string line, const std::vector<glm::vec3>& positions,
		const std::vector<glm::vec2>& texturePositions, const std::vector<glm::vec3>& normalVectors,
		Vertex triangle[]);
public:
	static void parse(std::string filename, std::vector<Vertex>& vertices);
};

#endif
