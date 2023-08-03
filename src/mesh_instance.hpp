#ifndef MESH_INSTANCE_HPP
#define MESH_INSTANCE_HPP

#include "mesh.hpp"
#include "movable.hpp"

#include <glm/glm.hpp>

class MeshInstance : public Movable
{
public:
	MeshInstance(const Mesh& mesh);
	void render(glm::mat4 modelMatrix) const;
	glm::mat4 getMatrix() const;
	virtual ~MeshInstance() = default;
	
protected:
	const Mesh& m_mesh;
};

#endif
