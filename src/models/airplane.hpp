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

#include <memory>

class Airplane : public Model
{
public:
	Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager,
		const AirplaneType& airplaneType);
	Airplane(const Airplane&);
	Airplane(Airplane&&) = default;
	
	virtual void initialize() override;
	void update(const Airplane& previousAirplane);
	void rotatePropeller(float angleDeg);
	virtual void updateShaders() override;

	void ctrl(const UserInput& input);
	// TODO: decide if delete ctrlPitch, ctrlYaw, ctrlRoll and ctrlThrust
	void ctrlPitch(float relative);
	void ctrlYaw(float relative);
	void ctrlRoll(float relative);
	void ctrlThrust(float relative);

	virtual ~Airplane() = default;

private:
	AirplaneType m_airplaneType;

	std::unique_ptr<Submodel> m_cap;
	std::unique_ptr<Submodel> m_propeller;
	std::unique_ptr<Submodel> m_body;
	std::unique_ptr<Submodel> m_joins;
	std::unique_ptr<Submodel> m_tires;
	std::unique_ptr<SpotLight> m_leftLight;
	std::unique_ptr<SpotLight> m_rightLight;

	FlightCtrl m_flightCtrl;
	AirplaneDynamics m_dynamics;

	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};
