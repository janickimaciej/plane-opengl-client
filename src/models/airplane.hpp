#ifndef AIRPLANE_HPP
#define AIRPLANE_HPP

#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "models/model.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/model_dynamics/airplane_dynamics.hpp"

class Airplane : public Model
{
public:
	Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const AirplaneParams& params);

	void update();
	void rotatePropeller(float angleDeg);

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

#endif
