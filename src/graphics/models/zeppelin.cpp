#include "graphics/models/zeppelin.hpp"

#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"

namespace Graphics
{
	const std::string modelName = "zeppelin";

	const std::string fuselagePath = meshPath(modelName, "body");

	const Material zeppelinCanvas{glm::vec3{0.9, 0.9, 0.9}, 0.75, 0.25, 10};

	Zeppelin::Zeppelin(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager) :
		Model{surfaceShaderProgram, lightShaderProgram},
		m_fuselage{surfaceShaderProgram, meshManager.get(fuselagePath), zeppelinCanvas}
	{
		constexpr float zeppelinScale = 57;
		scale(zeppelinScale);
	}

	void Zeppelin::updateShaders()
	{ }

	void Zeppelin::renderSurfaces() const
	{
		m_fuselage.render(getMatrix());
	}

	void Zeppelin::renderLights() const
	{ }
};
