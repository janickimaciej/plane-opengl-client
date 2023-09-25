#include "models/airplane.hpp"

#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/mesh_instance.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/model_dynamics/airplane_dynamics.hpp"

#include <glm/glm.hpp>

constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor{1, 1, 1};
constexpr float lightsCutoffInnerDeg = 8;
constexpr float lightsCutoffOuterDeg = 10;

Airplane::Airplane(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, const Mesh& capMesh, const Mesh& propellerMesh,
	const Mesh& bodyMesh, const Mesh& joinsMesh, const Mesh& tiresMesh, const Mesh& lightMesh,
	const AirplaneParams& params) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_cap{capMesh},
	m_propeller{propellerMesh},
	m_body{bodyMesh},
	m_joins{joinsMesh},
	m_tires{tiresMesh},
	m_leftLight{surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
		lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
		lightsCutoffOuterDeg, getMatrix()},
	m_rightLight{surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
		lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
		lightsCutoffOuterDeg, getMatrix()},
	m_flightCtrl{params},
	m_dynamics{params, m_flightCtrl}
{
	constexpr float lightsPositionXAbs = 2.14f;
	constexpr float lightsPositionY = -0.474f;
	constexpr float lightsPositionZ = 2.938f;
	m_leftLight.translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ},
		getMatrix());
	m_rightLight.translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ},
		getMatrix());

	m_cap.translate(params.inertia.nosePosition);
	m_propeller.translate(params.inertia.nosePosition);
	m_body.translate(params.inertia.nosePosition);
	m_joins.translate(params.inertia.nosePosition);
	m_tires.translate(params.inertia.nosePosition);
	m_leftLight.translate(params.inertia.nosePosition, getMatrix());
	m_rightLight.translate(params.inertia.nosePosition, getMatrix());

	updateShaderLightMatrix();
}

void Airplane::update()
{
	setState(m_dynamics.computeNewState(getState()));
}

void Airplane::rotatePropeller(float angleDeg)
{
	m_propeller.rotateRoll(angleDeg);
}

void Airplane::ctrlPitch(float relative)
{
	m_flightCtrl.ctrlPitch(relative);
}

void Airplane::ctrlYaw(float relative)
{
	m_flightCtrl.ctrlYaw(relative);
}

void Airplane::ctrlRoll(float relative)
{
	m_flightCtrl.ctrlRoll(relative);
}

void Airplane::ctrlThrust(float relative)
{
	m_flightCtrl.ctrlThrust(relative);
}

void Airplane::updateShaderLightMatrix() const
{
	m_leftLight.updateShaderLightTranslation(getMatrix());
	m_rightLight.updateShaderLightTranslation(getMatrix());
}

void Airplane::renderSurfaces() const
{
	m_cap.render(getMatrix());
	m_propeller.render(getMatrix());
	m_body.render(getMatrix());
	m_joins.render(getMatrix());
	m_tires.render(getMatrix());
}

void Airplane::renderLights() const
{
	m_leftLight.render(getMatrix());
	m_rightLight.render(getMatrix());
}
