#include "graphics/material.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	Material::Material(const glm::vec3& color, float diffuse, float specular, float shininess,
		bool isMetal) :
		color{color},
		diffuse{diffuse},
		specular{specular},
		shininess{shininess},
		isMetal{isMetal}
	{ }
};
