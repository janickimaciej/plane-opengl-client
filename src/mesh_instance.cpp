#include "mesh_instance.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

MeshInstance::MeshInstance(const Mesh& mesh) : mesh(mesh) { }

void MeshInstance::render(glm::mat4 modelMatrix) const {
	mesh.render(modelMatrix*matrix);
}

glm::mat4 MeshInstance::getMatrix() const {
	return matrix;
}
