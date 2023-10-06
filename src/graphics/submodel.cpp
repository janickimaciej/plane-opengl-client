#include "graphics/submodel.hpp"

#include "graphics/mesh.hpp"
#include "transformable.hpp"

#include <glm/glm.hpp>

Submodel::Submodel(const Mesh& mesh) :
	m_mesh{mesh}
{ }

void Submodel::render(const glm::mat4& modelMatrix) const
{
	m_mesh.render(modelMatrix * getMatrix());
}

void Submodel::scale(float scaleRatio)
{
	Transformable::scale(scaleRatio);
}

glm::mat4 Submodel::getMatrix() const
{
	return Transformable::getMatrix();
}
