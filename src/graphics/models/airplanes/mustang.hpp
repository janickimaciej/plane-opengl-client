#pragma once

#include "common/airplane_ctrl.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/light_submodel.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	class Mustang : public Airplane
	{
	public:
		Mustang(const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
			AssetManager<const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) override;

	private:
		Submodel m_cap;
		Submodel m_propeller;
		Submodel m_body;
		Submodel m_joins;
		Submodel m_tires;
		SpotLight m_leftLight;
		LightSubmodel m_leftLightSubmodel;
		SpotLight m_rightLight;
		LightSubmodel m_rightLightSubmodel;

		float m_propellerAngVelocityDeg{};

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
