#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>

struct Material
{
	glm::vec3 color{};
	float diffuse{};
	float specular{};
	float shininess{};

	Material(const glm::vec3& color, float diffuse, float specular, float shininess);
};

#endif
