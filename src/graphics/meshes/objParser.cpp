#include "graphics/meshes/objParser.hpp"

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> ObjParser::parse(const std::string& path)
	{
		std::ifstream file{path};
		if (!file)
		{
			std::cerr << "File does not exist:\n" << path << '\n';
			assert(false);
			return std::vector<Vertex>{};
		}
		
		std::vector<Vertex> vertices{};

		std::vector<glm::vec3> positions{};
		std::vector<glm::vec2> texturePositions{};
		std::vector<glm::vec3> normalVectors{};

		std::string line{};
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
				std::array<Vertex, 3> triangle =
					parseTriangle(line, positions, texturePositions, normalVectors);
				vertices.push_back(triangle[0]);
				vertices.push_back(triangle[1]);
				vertices.push_back(triangle[2]);
			}
		}

		return vertices;
	}

	glm::vec3 ObjParser::parsePosition(const std::string_view line)
	{
		glm::vec3 position{};

		int component = 0;
		std::string number = "";
		for (auto c = line.begin() + 2; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				position[component] = std::stof(number);
				++component;
				number = "";
			}
			else
			{
				number.push_back(*c);
			}
		}
		position[component] = std::stof(number);

		return position;
	}

	glm::vec2 ObjParser::parseTexturePosition(const std::string_view line)
	{
		glm::vec2 texturePosition{};

		int component = 0;
		std::string number = "";
		for (auto c = line.begin() + 3; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				texturePosition[component] = std::stof(number);
				++component;
				number = "";
			}
			else
			{
				number.push_back(*c);
			}
		}
		texturePosition[component] = std::stof(number);

		return texturePosition;
	}

	glm::vec3 ObjParser::parseNormalVector(const std::string_view line)
	{
		glm::vec3 normalVector{};

		int component = 0;
		std::string number = "";
		for (auto c = line.begin() + 3; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				normalVector[component] = std::stof(number);
				++component;
				number = "";
			}
			else
			{
				number.push_back(*c);
			}
		}
		normalVector[component] = std::stof(number);

		return normalVector;
	}

	std::array<Vertex, 3> ObjParser::parseTriangle(const std::string_view line,
		const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texturePositions,
		const std::vector<glm::vec3>& normalVectors)
	{
		std::array<Vertex, 3> triangle;

		std::size_t vertexIndex = 0;
		std::string number = "";
		std::size_t positionIndex = 0;
		std::size_t normalVectorIndex = 0;
		std::size_t texturePositionIndex = 0;
		bool isFirstNumber = true;
		for (auto c = line.begin() + 2; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				normalVectorIndex = static_cast<std::size_t>(std::stoi(number));
				number = "";
				if (vertexIndex < 3)
				{
					triangle[vertexIndex].position = positions[positionIndex - 1];
					triangle[vertexIndex].texturePosition =
						texturePositions[texturePositionIndex - 1];
					triangle[vertexIndex].normalVector = normalVectors[normalVectorIndex - 1];
				}
				++vertexIndex;
			}
			else if (*c == '/')
			{
				if (isFirstNumber)
				{
					positionIndex = static_cast<std::size_t>(std::stoi(number));
				}
				else
				{
					texturePositionIndex = static_cast<std::size_t>(std::stoi(number));
				}
				number = "";
				isFirstNumber = !isFirstNumber;
			}
			else
			{
				number.push_back(*c);
			}
		}
		normalVectorIndex = static_cast<std::size_t>(std::stoi(number));
		if (vertexIndex < 3)
		{
			triangle[vertexIndex].position = positions[positionIndex - 1];
			triangle[vertexIndex].texturePosition = texturePositions[texturePositionIndex - 1];
			triangle[vertexIndex].normalVector = normalVectors[normalVectorIndex - 1];
		}
		
		return triangle;
	}
};
