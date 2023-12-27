#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"

namespace Graphics
{
	class Zeppelin : public Model
	{
	public:
		Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<const Mesh>& meshManager);
		virtual void updateShaders() override;
		virtual ~Zeppelin() = default;

	private:
		Submodel m_fuselage;

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
