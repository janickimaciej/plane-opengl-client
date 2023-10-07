#include "models/zeppelin.hpp"

#include "graphics/mesh.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"
#include "models/model.hpp"

#include <memory>

const Material zeppelinCanvas{glm::vec3{0.9, 0.9, 0.9}, 0.75, 0.25, 10};

Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_body{surfaceShaderProgram, std::make_shared<const Mesh>(SM_ZEPPELIN_BODY), zeppelinCanvas}
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
