#pragma once

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"

#include <string>

namespace Graphics
{
	class Zeppelin : public Model
	{
	public:
		Zeppelin(const ShaderProgram& surfaceShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~Zeppelin() = default;

	private:
		const ShaderProgram& m_surfaceShaderProgram;

		Submodel m_body;

		void renderSurfaces() const;
	};
};
