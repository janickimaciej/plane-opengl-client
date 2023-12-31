#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"

#include <string>

namespace Graphics
{
	class Zeppelin : public Model
	{
	public:
		Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager);
		virtual void updateShaders() override;
		virtual ~Zeppelin() = default;

	private:
		Submodel m_body;

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
