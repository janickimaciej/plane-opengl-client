#pragma once

#include "common/airplaneCtrl.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/lights/pointLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <string>

namespace Graphics
{
	class JW1 : public Airplane
	{
	public:
		JW1(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<std::string, const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) override;
		virtual void setHP(int hp) override;

	private:
		const ShaderProgram& m_surfaceShaderProgram;
		const ShaderProgram& m_lightShaderProgram;

		Submodel m_cone;
		Submodel m_gun;
		Submodel m_cockpit;
		Submodel m_fuselage;
		Submodel m_leftEngine;
		Submodel m_rightEngine;
		Submodel m_leftNozzle;
		Submodel m_rightNozzle;
		Submodel m_leftNozzleGlass;
		Submodel m_rightNozzleGlass;
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

		bool m_isDestroyed = false;

		void renderSurfaces() const;
		void renderLights() const;
	};
};
