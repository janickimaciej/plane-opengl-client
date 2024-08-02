#pragma once

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	class TextField
	{
	public:
		TextField(const ShaderProgram& hudShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager, const std::string& text,
			const glm::vec3& offset, float scaleRatio);
		void setCharacter(std::size_t index, char character);
		void render(const glm::mat4& modelMatrix) const;

	private:
		std::vector<Submodel> m_textSubmodels{};
		AssetManager<std::string, const Texture>& m_textureManager;
	};
};
