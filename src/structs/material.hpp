#ifndef MATERIAL
#define MATERIAL

#include <glm/glm.hpp>

struct Material {
	glm::vec3 color;
	float diffuse;
	float specular;
	float shininess;

	Material(glm::vec3 color, float diffuse, float specular, float shininess);
};

#endif
