#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	struct Material
	{
		glm::vec3 color{};
		float diffuse{};
		float specular{};
		float shininess{};

		Material(const glm::vec3& color, float diffuse, float specular, float shininess);
	};
};
