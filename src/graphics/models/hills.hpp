#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <string>

namespace Graphics
{
	class Hills : public Model
	{
	public:
		Hills(const ShaderProgram& surfaceShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~Hills() = default;

	private:
		const ShaderProgram& m_surfaceShaderProgram;

		Submodel m_ground;
		
		void renderSurfaces() const;
	};
};
