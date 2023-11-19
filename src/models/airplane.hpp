#pragma once

#include "airplane_type.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"
#include "models/model.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/model_dynamics/airplane_dynamics.hpp"
#include "sync/user_input.hpp"

class Airplane : public Model
{
public:
	Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager,
		const AirplaneType& type);

	void update(const Airplane& previousAirplane);
	void rotatePropeller(float angleDeg);

	void ctrl(const UserInput& input);
	// TODO: decide if delete ctrlPitch, ctrlYaw, ctrlRoll and ctrlThrust
	void ctrlPitch(float relative);
	void ctrlYaw(float relative);
	void ctrlRoll(float relative);
	void ctrlThrust(float relative);

	virtual ~Airplane() = default;

private:
	Submodel m_cap;
	Submodel m_propeller;
	Submodel m_body;
	Submodel m_joins;
	Submodel m_tires;
	SpotLight m_leftLight;
	SpotLight m_rightLight;

	FlightCtrl m_flightCtrl;
	AirplaneDynamics m_dynamics;

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};
