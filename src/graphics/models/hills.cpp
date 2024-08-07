#include "graphics/models/hills.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	const std::string modelName = "hills";

	const std::string grassPath = texturePath(modelName, "grass");

	const Material ground{glm::vec3{1, 1, 1}, 0.75, 0, 10, false};

	Hills::Hills(const ShaderProgram& surfaceShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_ground{surfaceShaderProgram, proceduralMeshManager.get(ProceduralMeshName::hills), ground,
			textureManager.get(grassPath)}
	{ }

	void Hills::updateShaders()
	{ }

	void Hills::render() const
	{
		m_surfaceShaderProgram.use();
		renderSurfaces();
	}

	void Hills::renderSurfaces() const
	{
		m_ground.render(getMatrix());
	}
};
