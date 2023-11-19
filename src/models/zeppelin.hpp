#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "models/model.hpp"

#include <memory>

class Zeppelin : public Model
{
public:
	Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
	virtual void initialize() override;
	virtual void updateShaders() override;
	virtual ~Zeppelin() = default;

private:
	std::unique_ptr<Submodel> m_body;

	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};
