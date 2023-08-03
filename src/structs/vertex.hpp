#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position {};
	glm::vec2 texturePosition {};
	glm::vec3 normalVector {};
};

#endif
