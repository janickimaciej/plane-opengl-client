#include "mesh_instance.hpp"

#include "mesh.hpp"
#include "movable.hpp"

#include <glm/glm.hpp>

MeshInstance::MeshInstance(const Mesh& mesh) :
	m_mesh { mesh }
{ }

void MeshInstance::render(glm::mat4 modelMatrix) const
{
	m_mesh.render(modelMatrix * m_matrix);
}

glm::mat4 MeshInstance::getMatrix() const
{
	return m_matrix;
}
