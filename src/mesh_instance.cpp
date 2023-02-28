#include "mesh_instance.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void MeshInstance::updateShaderMeshMatrix() const {
	mesh.getShaderProgram().setUniformMatrix4f("meshMatrix", matrix);
}

MeshInstance::MeshInstance(const Mesh& mesh) : mesh(mesh) { }

void MeshInstance::render() const {
	updateShaderMeshMatrix();
	mesh.render();
}

glm::mat4 MeshInstance::getMatrix() const {
	return matrix;
}
