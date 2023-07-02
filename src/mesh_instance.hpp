#ifndef MESH_INSTANCE
#define MESH_INSTANCE

#include "movable.hpp"
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "shader_program.hpp"

class MeshInstance : public Movable {
protected:
	const Mesh& mesh;

	void updateShaderMeshMatrix() const;
public:
	MeshInstance(const Mesh& mesh);
	void render() const;
	glm::mat4 getMatrix() const;
	virtual ~MeshInstance() = default;
};

#endif
