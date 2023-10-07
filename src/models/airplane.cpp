#include "models/airplane.hpp"

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
	const ShaderProgram& lightShaderProgram, const AirplaneParams& params) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_cap{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPLANE_CAP), metal},
	m_propeller{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPLANE_PROPELLER), metal},
	m_body{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPLANE_BODY), defaultMaterial,
		std::make_shared<const Texture>(T_CAMO)},
	m_joins{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPLANE_JOINS), metal},
	m_tires{surfaceShaderProgram, std::make_shared<const Mesh>(SM_AIRPLANE_TIRES), rubber},
	m_leftLight{surfaceShaderProgram, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg,
		getMatrix(), Submodel{lightShaderProgram, make_shared<const Mesh>(SM_AIRPLANE_LIGHT),
		whiteLightGlass}},
	m_rightLight{surfaceShaderProgram, lightsAttenuationQuadratic, lightsAttenuationLinear,
		lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg,
		getMatrix(), Submodel{lightShaderProgram, make_shared<const Mesh>(SM_AIRPLANE_LIGHT),
		whiteLightGlass}},
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
