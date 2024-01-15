#include "graphics/models/bullet.hpp"

namespace Graphics
{
	const Material tracer{glm::vec3{1, 1, 1}, 1, 1, 1, false};

	Bullet::Bullet(const ShaderProgram& lightShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager) :
		m_lightShaderProgram{lightShaderProgram},
		m_tracer{lightShaderProgram, proceduralMeshManager.get(ProceduralMeshName::bullet), tracer}
	{ }

	void Bullet::updateShaders()
	{ }

	void Bullet::render() const
	{
		m_lightShaderProgram.use();
		renderLights();
	}

	void Bullet::renderLights() const
	{
		m_tracer.render(getMatrix());
	}
};
