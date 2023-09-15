#ifndef AIRPLANE_HPP
#define AIRPLANE_HPP

#include "flight_ctrl.hpp"
#include "lights/spot_light.hpp"
#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "model_dynamics/airplane_dynamics.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"
#include "structs/airplane_params.hpp"

class Airplane : public Model
{
public:
	Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& capMesh, const Mesh& propellerMesh, const Mesh& bodyMesh, const Mesh& joinsMesh,
		const Mesh& tiresMesh, const Mesh& lightMesh, const AirplaneParams& params);
	void update();
	void rotatePropeller(float angleDeg);
	virtual ~Airplane() = default;

private:
	MeshInstance m_cap;
	MeshInstance m_propeller;
	MeshInstance m_body;
	MeshInstance m_joins;
	MeshInstance m_tires;
	SpotLight m_leftLight;
	SpotLight m_rightLight;

	AirplaneParams m_params;
	FlightCtrl m_flightCtrl;
	AirplaneDynamics m_dynamics;

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};

#endif
