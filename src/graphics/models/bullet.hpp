#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"

namespace Graphics
{
	class Bullet : public Model
	{
	public:
		Bullet(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager);
		virtual void updateShaders() override;
		virtual ~Bullet() = default;
		
	private:
		Submodel m_tracer;

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
