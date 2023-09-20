#ifndef AIRPLANE_HPP
#define AIRPLANE_HPP

#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/mesh_instance.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"
#include "physics/airplane_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/model_dynamics/airplane_dynamics.hpp"

class Airplane : public Model
{
public:
	Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& capMesh, const Mesh& propellerMesh, const Mesh& bodyMesh, const Mesh& joinsMesh,
		const Mesh& tiresMesh, const Mesh& lightMesh, const AirplaneParams& params);

	void update();
	void rotatePropeller(float angleDeg);

	void ctrlPitch(float relative);
	void ctrlYaw(float relative);
	void ctrlRoll(float relative);
	void ctrlThrust(float relative);

	virtual ~Airplane() = default;

private:
	MeshInstance m_cap;
	MeshInstance m_propeller;
	MeshInstance m_body;
	MeshInstance m_joins;
	MeshInstance m_tires;
	SpotLight m_leftLight;
	SpotLight m_rightLight;

	const AirplaneParams& m_params;
	FlightCtrl m_flightCtrl;
	AirplaneDynamics m_dynamics;

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};

#endif
