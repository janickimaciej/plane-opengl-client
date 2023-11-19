#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"
#include "models/model.hpp"

#include <memory>
#include <vector>

class Airport : public Model
{
public:
	Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
	virtual void initialize() override;
	virtual void updateShaders() override;
	virtual ~Airport() = default;

private:
	std::unique_ptr<Submodel> m_ground;
	std::unique_ptr<Submodel> m_runway;
	std::unique_ptr<Submodel> m_apron;
	std::unique_ptr<Submodel> m_tower;
	std::vector<Submodel> m_hangars{};
	std::vector<Submodel> m_lightBodies{};
	std::vector<SpotLight> m_lights{};

	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};
