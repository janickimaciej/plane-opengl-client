#include "models/zeppelin.hpp"

#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "models/model.hpp"

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
