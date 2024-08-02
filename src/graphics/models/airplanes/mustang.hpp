#pragma once

#include "common/airplaneCtrl.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/lightSubmodel.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <string>

namespace Graphics
{
	class Mustang : public Airplane
	{
	public:
		Mustang(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<std::string, const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) override;
		virtual void setHP(int hp) override;

	private:
		const ShaderProgram& m_surfaceShaderProgram;
		const ShaderProgram& m_lightShaderProgram;

		Submodel m_cap;
		Submodel m_propeller;
		Submodel m_body;
		Submodel m_joins;
		Submodel m_tires;
		SpotLight m_leftLight;
		LightSubmodel m_leftLightSubmodel;
		SpotLight m_rightLight;
		LightSubmodel m_rightLightSubmodel;

		bool m_isDestroyed = false;
		float m_propellerAngVelocityDeg{};

		void renderSurfaces() const;
		void renderLights() const;
	};
};
