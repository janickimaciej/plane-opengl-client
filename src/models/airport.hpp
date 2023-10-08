#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"
#include "models/model.hpp"

#include <vector>

class Airport : public Model
{
public:
	Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
	virtual ~Airport() = default;

private:
	Submodel m_ground;
	Submodel m_runway;
	Submodel m_apron;
	Submodel m_tower;
	std::vector<Submodel> m_hangars{};
	std::vector<Submodel> m_lightBodies{};
	std::vector<SpotLight> m_lights{};

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};

#endif
