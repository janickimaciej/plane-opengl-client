#include "obj_parser.hpp"

#include "structs/vertex.hpp"

#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void ObjParser::parse(const std::string& filename, std::vector<Vertex>& vertices)
{
	std::vector<glm::vec3> positions {};
	std::vector<glm::vec2> texturePositions {};
	std::vector<glm::vec3> normalVectors {};

	std::ifstream file { filename };
	if (!file)
	{
		std::cerr << "File does not exist:\n" << filename << '\n';
		return;
	}

	std::string line {};
	while (std::getline(file, line))
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			positions.push_back(parsePosition(line));
		}
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
		{
			texturePositions.push_back(parseTexturePosition(line));
		}
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
		{
			normalVectors.push_back(parseNormalVector(line));
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			Vertex triangle[3];
			parseTriangle(line, positions, texturePositions, normalVectors, triangle);
			vertices.push_back(triangle[0]);
			vertices.push_back(triangle[1]);
			vertices.push_back(triangle[2]);
		}
	}

	file.close();
}

glm::vec3 ObjParser::parsePosition(const std::string& line)
{
	glm::vec3 position { 0, 0, 0 };
	size_t component = 0;

	std::string number = "";
	for (size_t i = 2; i <= line.length(); ++i)
	{
		char c = line[i];
		if (c == ' ' || c == '\0')
		{
			position[component] = std::stof(number);
			++component;
			number = "";
		}
		else
		{
			number.push_back(c);
		}
	}

	return position;
}

glm::vec2 ObjParser::parseTexturePosition(const std::string& line)
{
	glm::vec2 texturePosition(0, 0);
	size_t component = 0;

	std::string number = "";
	for (size_t i = 3; i <= line.length(); ++i)
	{
		char c = line[i];
		if (c == ' ' || c == '\0')
		{
			texturePosition[component] = std::stof(number);
			++component;
			number = "";
		}
		else
		{
			number.push_back(c);
		}
	}

	return texturePosition;
}

glm::vec3 ObjParser::parseNormalVector(const std::string& line)
{
	glm::vec3 normalVector { 0, 0, 0 };
	size_t component = 0;

	std::string number = "";
	for (size_t i = 3; i <= line.length(); ++i)
	{
		char c = line[i];
		if (c == ' ' || c == '\0')
		{
			normalVector[component] = std::stof(number);
			++component;
			number = "";
		}
		else
		{
			number.push_back(c);
		}
	}

	return normalVector;
}

void ObjParser::parseTriangle(const std::string& line, const std::vector<glm::vec3>& positions,
	const std::vector<glm::vec2>& texturePositions, const std::vector<glm::vec3>& normalVectors,
	Vertex triangle[])
{
	size_t vertexIndex = 0;

	std::string number = "";
	size_t positionIndex = 0;
	size_t normalVectorIndex = 0;
	size_t texturePositionIndex = 0;
	bool isFirstNumber = true;
	for (size_t i = 2; i <= line.length(); ++i)
	{
		char c = line[i];
		if (c == ' ' || c == '\0')
		{
			normalVectorIndex = (unsigned int)std::stoi(number);
			number = "";

			triangle[vertexIndex].position = positions[positionIndex - 1];
			triangle[vertexIndex].texturePosition = texturePositions[texturePositionIndex - 1];
			triangle[vertexIndex].normalVector = normalVectors[normalVectorIndex - 1];
			++vertexIndex;
		}
		else if (c == '/')
		{
			if (isFirstNumber)
			{
				positionIndex = (unsigned int)std::stoi(number);
			}
			else
			{
				texturePositionIndex = (unsigned int)std::stoi(number);
			}
			number = "";
			isFirstNumber = !isFirstNumber;
		}
		else
		{
			number.push_back(c);
		}
	}
}
