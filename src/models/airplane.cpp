#include "models/airplane.hpp"

#include "airplane_type.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"
#include "models/model.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/flight_ctrl.hpp"
#include "physics/model_dynamics/airplane_dynamics.hpp"
#include "sync/user_input.hpp"

#include <glm/glm.hpp>

constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor{1, 1, 1};
constexpr float lightsCutoffInnerDeg = 8;
constexpr float lightsCutoffOuterDeg = 10;

// dummy color
const Material defaultMaterial{glm::vec3{1, 0, 0}, 0.75, 0.25, 10};
const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.25, 10};
const Material rubber{glm::vec3{0.1, 0.1, 0.1}, 0.75, 0.25, 10};
// dummy surface params
const Material whiteLightGlass{glm::vec3{1, 1, 1}, 1, 1, 1};

Airplane::Airplane(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
	AssetManager<const Texture>& textureManager, const AirplaneType& type) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_cap{surfaceShaderProgram, meshManager.get(type.cap), metal},
	m_propeller{surfaceShaderProgram, meshManager.get(type.propeller), metal},
	m_body{surfaceShaderProgram, meshManager.get(type.body), defaultMaterial,
		textureManager.get(type.camo)},
	m_joins{surfaceShaderProgram, meshManager.get(type.joins), metal},
	m_tires{surfaceShaderProgram, meshManager.get(type.tires), rubber},
	m_leftLight{surfaceShaderProgram, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg,
		getMatrix(), Submodel{lightShaderProgram, meshManager.get(type.light),
		whiteLightGlass}},
	m_rightLight{surfaceShaderProgram, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg,
		getMatrix(), Submodel{lightShaderProgram, meshManager.get(type.light),
		whiteLightGlass}},
	m_flightCtrl{type.params},
	m_dynamics{type.params, m_flightCtrl}
{
	constexpr float lightsPositionXAbs = 2.14f;
	constexpr float lightsPositionY = -0.474f;
	constexpr float lightsPositionZ = 2.938f;
	m_leftLight.translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ},
		getMatrix());
	m_rightLight.translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ},
		getMatrix());

	m_cap.translate(type.params.inertia.nosePosition);
	m_propeller.translate(type.params.inertia.nosePosition);
	m_body.translate(type.params.inertia.nosePosition);
	m_joins.translate(type.params.inertia.nosePosition);
	m_tires.translate(type.params.inertia.nosePosition);
	m_leftLight.translate(type.params.inertia.nosePosition, getMatrix());
	m_rightLight.translate(type.params.inertia.nosePosition, getMatrix());

	updateShaderLightMatrix();
}

void Airplane::update(const Airplane& previousAirplane)
{
	setState(m_dynamics.computeNewState(previousAirplane.getState()));
}

void Airplane::rotatePropeller(float angleDeg)
{
	m_propeller.rotateRoll(angleDeg);
}

void Airplane::ctrl(const UserInput& input)
{
	ctrlPitch(input.pitch);
	ctrlYaw(input.yaw);
	ctrlRoll(input.roll);
	ctrlThrust(input.thrust);
	// TODO: ctrlTrigger
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
