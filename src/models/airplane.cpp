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

#include <memory>

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
	AssetManager<const Texture>& textureManager, const AirplaneType& airplaneType) :
	Model{surfaceShaderProgram, lightShaderProgram, meshManager, textureManager},
	m_airplaneType{airplaneType},
	m_flightCtrl{airplaneType.params},
	m_dynamics{airplaneType.params, m_flightCtrl}
{ }

Airplane::Airplane(const Airplane& airplane) :
	Model{airplane.m_surfaceShaderProgram, m_lightShaderProgram, m_meshManager, m_textureManager},
	m_airplaneType{airplane.m_airplaneType},
	m_cap{std::make_unique<Submodel>(*airplane.m_cap)},
	m_propeller{std::make_unique<Submodel>(*airplane.m_propeller)},
	m_body{std::make_unique<Submodel>(*airplane.m_body)},
	m_joins{std::make_unique<Submodel>(*airplane.m_joins)},
	m_tires{std::make_unique<Submodel>(*airplane.m_tires)},
	m_leftLight{std::make_unique<SpotLight>(*airplane.m_leftLight)},
	m_rightLight{std::make_unique<SpotLight>(*airplane.m_rightLight)},
	m_flightCtrl{airplane.m_flightCtrl},
	m_dynamics{airplane.m_dynamics}
{ }

void Airplane::initialize()
{
	m_cap = std::make_unique<Submodel>(m_surfaceShaderProgram,
		m_meshManager.get(m_airplaneType.cap), metal);
	m_propeller = std::make_unique<Submodel>(m_surfaceShaderProgram,
		m_meshManager.get(m_airplaneType.propeller), metal);
	m_body = std::make_unique<Submodel>(m_surfaceShaderProgram,
		m_meshManager.get(m_airplaneType.body), defaultMaterial,
		m_textureManager.get(m_airplaneType.camo));
	m_joins = std::make_unique<Submodel>(m_surfaceShaderProgram,
		m_meshManager.get(m_airplaneType.joins), metal);
	m_tires = std::make_unique<Submodel>(m_surfaceShaderProgram,
		m_meshManager.get(m_airplaneType.tires), rubber);
	m_leftLight = std::make_unique<SpotLight>(m_surfaceShaderProgram, lightsAttenuationQuadratic,
		lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
		lightsCutoffOuterDeg, Submodel{m_lightShaderProgram,
		m_meshManager.get(m_airplaneType.light), whiteLightGlass});
	m_rightLight = std::make_unique<SpotLight>(m_surfaceShaderProgram, lightsAttenuationQuadratic,
		lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
		lightsCutoffOuterDeg, Submodel{m_lightShaderProgram,
		m_meshManager.get(m_airplaneType.light), whiteLightGlass});

	constexpr float lightsPositionXAbs = 2.14f;
	constexpr float lightsPositionY = -0.474f;
	constexpr float lightsPositionZ = 2.938f;
	m_leftLight->translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ});
	m_rightLight->translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ});

	m_cap->translate(m_airplaneType.params.inertia.nosePosition);
	m_propeller->translate(m_airplaneType.params.inertia.nosePosition);
	m_body->translate(m_airplaneType.params.inertia.nosePosition);
	m_joins->translate(m_airplaneType.params.inertia.nosePosition);
	m_tires->translate(m_airplaneType.params.inertia.nosePosition);
	m_leftLight->translate(m_airplaneType.params.inertia.nosePosition);
	m_rightLight->translate(m_airplaneType.params.inertia.nosePosition);
}

void Airplane::update(const Airplane& previousAirplane)
{
	setState(m_dynamics.computeNewState(previousAirplane.getState()));
}

void Airplane::rotatePropeller(float angleDeg)
{
	m_propeller->rotateRoll(angleDeg);
}

void Airplane::updateShaders()
{
	tryInitializing();
	m_leftLight->updateShaders(getMatrix());
	m_rightLight->updateShaders(getMatrix());
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

void Airplane::renderSurfaces() const
{
	m_cap->render(getMatrix());
	m_propeller->render(getMatrix());
	m_body->render(getMatrix());
	m_joins->render(getMatrix());
	m_tires->render(getMatrix());
}

void Airplane::renderLights() const
{
	m_leftLight->render(getMatrix());
	m_rightLight->render(getMatrix());
}
