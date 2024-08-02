#pragma once

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"

namespace Graphics
{
	class Bullet : public Model
	{
	public:
		Bullet(const ShaderProgram& lightShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~Bullet() = default;
		
	private:
		const ShaderProgram& m_lightShaderProgram;

		Submodel m_tracer;

		void renderLights() const;
	};
};
