#include "models/zeppelin.hpp"

#include "graphics/mesh.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "models/model.hpp"

#include <memory>

const Material zeppelinCanvas{glm::vec3{0.9, 0.9, 0.9}, 0.75, 0.25, 10};

Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
	AssetManager<const Texture>& textureManager) :
	Model{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager}
{
	constexpr float zeppelinScale = 57;
	scale(zeppelinScale);
}

void Zeppelin::initialize()
{
	m_body = std::make_unique<Submodel>(m_surfaceShaderProgram, m_meshManager.get(SM_ZEPPELIN_BODY),
		zeppelinCanvas);
}

void Zeppelin::updateShaders()
{
	tryInitializing();
}

void Zeppelin::renderSurfaces() const
{
	m_body->render(getMatrix());
}

void Zeppelin::renderLights() const
{ }
