#include "obj_parser.hpp"
#include <iostream>
#include <fstream>

void ObjParser::parse(std::string filename, std::vector<Vertex>& vertices) {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texturePositions;
	std::vector<glm::vec3> normalVectors;

	std::ifstream file(filename);
	if(!file) {
		std::cerr << "File does not exist." << std::endl;
		return;
	}

	std::string line;
	while(std::getline(file, line)) {
		if(line[0] == 'v' && line[1] == ' ') {
			positions.push_back(parsePosition(line));
		} else if(line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			texturePositions.push_back(parseTexturePosition(line));
		} else if(line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			normalVectors.push_back(parseNormalVector(line));
		} else if(line[0] == 'f' && line[1] == ' ') {
			Vertex triangle[3];
			parseTriangle(line, positions, texturePositions, normalVectors, triangle);
			vertices.push_back(triangle[0]);
			vertices.push_back(triangle[1]);
			vertices.push_back(triangle[2]);
		}
	}
}

glm::vec3 ObjParser::parsePosition(std::string line) {
	glm::vec3 position(0, 0, 0);
	int component = 0;

	std::string number = "";
	for(int i = 2; i <= line.length(); i++) {
		char c = line[i];
		if(c == ' ' || c == '\0') {
			position[component++] = std::stof(number);
			number = "";
		} else {
			number.push_back(c);
		}
	}

	return position;
}

glm::vec2 ObjParser::parseTexturePosition(std::string line) {
	glm::vec2 texturePosition(0, 0);
	int component = 0;

	std::string number = "";
	for(int i = 3; i <= line.length(); i++) {
		char c = line[i];
		if(c == ' ' || c == '\0') {
			texturePosition[component++] = std::stof(number);
			number = "";
		} else {
			number.push_back(c);
		}
	}

	return texturePosition;
}

glm::vec3 ObjParser::parseNormalVector(std::string line) {
	glm::vec3 normalVector(0, 0, 0);
	int component = 0;

	std::string number = "";
	for(int i = 3; i <= line.length(); i++) {
		char c = line[i];
		if(c == ' ' || c == '\0') {
			normalVector[component++] = std::stof(number);
			number = "";
		} else {
			number.push_back(c);
		}
	}

	return normalVector;
}

void ObjParser::parseTriangle(std::string line, const std::vector<glm::vec3>& positions,
	const std::vector<glm::vec2>& texturePositions, const std::vector<glm::vec3>& normalVectors,
	Vertex triangle[]) {
	int vertexIndex = 0;

	std::string number = "";
	int positionIndex = 0;
	int normalVectorIndex = 0;
	int texturePositionIndex = 0;
	bool isFirstNumber = true;
	for(int i = 2; i <= line.length(); i++) {
		char c = line[i];
		if(c == ' ' || c == '\0') {
			normalVectorIndex = std::stoi(number);
			number = "";

			triangle[vertexIndex].position = positions[positionIndex - 1];
			triangle[vertexIndex].texturePosition = texturePositions[texturePositionIndex - 1];
			triangle[vertexIndex].normalVector = normalVectors[normalVectorIndex - 1];
			vertexIndex++;
		} else if(c == '/') {
			if(isFirstNumber) {
				positionIndex = std::stoi(number);
			} else {
				texturePositionIndex = std::stoi(number);
			}
			number = "";
			isFirstNumber = !isFirstNumber;
		} else {
			number.push_back(c);
		}
	}
}
