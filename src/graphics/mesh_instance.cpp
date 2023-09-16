#include "graphics/mesh_instance.hpp"

#include "graphics/mesh.hpp"
#include "movable.hpp"

#include <glm/glm.hpp>

MeshInstance::MeshInstance(const Mesh& mesh) :
	m_mesh{mesh}
{ }

void MeshInstance::render(const glm::mat4& modelMatrix) const
{
	m_mesh.render(modelMatrix * getMatrix());
}

glm::mat4 MeshInstance::getMatrix() const
{
	return Movable::getMatrix();
}
