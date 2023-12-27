#pragma once

#include "common/airplane_ctrl.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/point_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	class JW1 : public Airplane
	{
	public:
		JW1(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) override;

	private:
		Submodel m_cone;
		Submodel m_gun;
		Submodel m_cockpit;
		Submodel m_fuselage;
		Submodel m_leftEngine;
		Submodel m_rightEngine;
		Submodel m_leftNozzle;
		Submodel m_rightNozzle;
		Submodel m_leftWing;
		Submodel m_rightWing;
		Submodel m_leftVStab;
		Submodel m_rightVStab;
		Submodel m_leftElevator;
		Submodel m_rightElevator;
		Submodel m_leftRudder;
		Submodel m_rightRudder;
		Submodel m_leftAileron;
		Submodel m_rightAileron;
		PointLight m_leftNozzleLight;
		PointLight m_rightNozzleLight;

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
