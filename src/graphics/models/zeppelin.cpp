#include "graphics/models/zeppelin.hpp"

#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"

#include <string>

namespace Graphics
{
	const std::string modelName = "zeppelin";

	const std::string fuselagePath = meshPath(modelName, "body");

	const Material canvas{glm::vec3{0.9, 0.9, 0.9}, 0.75, 0.25, 10, false};

	Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager) :
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_body{surfaceShaderProgram, fileMeshManager.get(fuselagePath), canvas}
	{
		static constexpr float zeppelinScale = 57;
		scale(zeppelinScale);
	}

	void Zeppelin::updateShaders()
	{ }

	void Zeppelin::render() const
	{
		m_surfaceShaderProgram.use();
		renderSurfaces();
	}

	void Zeppelin::renderSurfaces() const
	{
		m_body.render(getMatrix());
	}
};
