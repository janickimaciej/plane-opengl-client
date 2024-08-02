#pragma once

#include "graphics/assetManager.hpp"
#include "graphics/lights/pointLight.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/lightSubmodel.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Graphics
{
	class Airport : public Model
	{
	public:
		Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<std::string, const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~Airport() = default;

	private:
		const ShaderProgram& m_surfaceShaderProgram;
		const ShaderProgram& m_lightShaderProgram;

		Submodel m_ground;
		Submodel m_runway;
		Submodel m_apron;
		Submodel m_tower;
		std::vector<Submodel> m_hangarExteriors{};
		std::vector<Submodel> m_hangarInteriors{};
		std::vector<Submodel> m_lightBodies{};
		std::vector<std::unique_ptr<SpotLight>> m_lights{};
		std::vector<LightSubmodel> m_lightSubmodels{};

		void renderSurfaces() const;
		void renderLights() const;
	};
};
