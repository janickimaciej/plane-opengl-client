#include "graphics/models/hills.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	const std::string modelName = "hills";

	const std::string grassPath = texturePath(modelName, "grass");

	const Material ground{glm::vec3{1, 1, 1}, 0.75, 0, 10, false};

	Hills::Hills(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		Model{surfaceShaderProgram, lightShaderProgram},
		m_ground{surfaceShaderProgram, proceduralMeshManager.get(ProceduralMeshName::hills), ground,
			textureManager.get(grassPath)}
	{ }

	void Hills::updateShaders()
	{ }

	void Hills::renderSurfaces() const
	{
		m_ground.render(getMatrix());
	}

	void Hills::renderLights() const
	{ }
};
