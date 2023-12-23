#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/lights/point_light.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/light_submodel.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <vector>

namespace Graphics
{
	class Airport : public Model
	{
	public:
		Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual ~Airport() = default;

	private:
		Submodel m_ground;
		Submodel m_runway;
		Submodel m_apron;
		Submodel m_tower;
		std::vector<Submodel> m_hangars{};
		std::vector<Submodel> m_lightBodies{};
		std::vector<std::unique_ptr<SpotLight>> m_lights{};
		std::vector<LightSubmodel> m_lightSubmodels{};
		PointLight m_pointLight;

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
