#ifndef SUBMODEL_HPP
#define SUBMODEL_HPP

#include "graphics/mesh.hpp"
#include "transformable.hpp"

#include <glm/glm.hpp>

class Submodel : public Transformable
{
public:
	Submodel(const Mesh& mesh);
	void render(const glm::mat4& modelMatrix) const;
	void scale(float scaleRatio);
	glm::mat4 getMatrix() const;
	virtual ~Submodel() = default;
	
protected:
	const Mesh& m_mesh;
};

#endif
