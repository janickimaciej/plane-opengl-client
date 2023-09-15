#include "models/zeppelin.hpp"

#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, const Mesh& bodyMesh) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_body{bodyMesh}
{
	constexpr float zeppelinScale = 57;
	scale(zeppelinScale);
	updateShaderLightMatrix();
}

void Zeppelin::updateShaderLightMatrix() const
{ }

void Zeppelin::renderSurfaces() const
{
	m_body.render(getMatrix());
}

void Zeppelin::renderLights() const
{ }
