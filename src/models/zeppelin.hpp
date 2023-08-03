#ifndef ZEPPELIN_HPP
#define ZEPPELIN_HPP

#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

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
