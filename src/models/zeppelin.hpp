#ifndef ZEPPELIN_HPP
#define ZEPPELIN_HPP

#include "graphics/mesh.hpp"
#include "graphics/mesh_instance.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

class Zeppelin : public Model
{
public:
	Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& bodyMesh);
	virtual ~Zeppelin() = default;

private:
	MeshInstance m_body;

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};

#endif
