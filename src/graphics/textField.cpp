#include "graphics/textField.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/config.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	const std::string modelName = "characters";

	TextField::TextField(const ShaderProgram& hudShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager, const std::string& text,
		const glm::vec3& offset, float scaleRatio) :
		m_textureManager{textureManager}
	{
		const Material billboard{glm::vec3{1, 1, 1}, 1, 1, 1, false};
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			Submodel submodel
			{
					hudShaderProgram,
					proceduralMeshManager.get(ProceduralMeshName::characterBillboard),
					billboard,
					textureManager.get(texturePath(modelName, std::string{text[i]}))
			};
			submodel.translate(offset);
			submodel.translate(glm::vec3{static_cast<int>(i) * scaleRatio * characterWidth, 0, 0});
			submodel.scale(scaleRatio);
			m_textSubmodels.push_back(submodel);
		}
	}

	void TextField::setCharacter(std::size_t index, char character)
	{
		if (index < 0 || index >= m_textSubmodels.size())
		{
			return;
		}
		m_textSubmodels[index].setTexture(m_textureManager.get(texturePath(modelName,
			std::string{character})));
	}

	void TextField::render(const glm::mat4& modelMatrix) const
	{
		for (const Submodel& submodel : m_textSubmodels)
		{
			submodel.render(modelMatrix);
		}
	}
};
