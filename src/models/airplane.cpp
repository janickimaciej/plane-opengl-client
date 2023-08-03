#include "models/airplane.hpp"

#include "flight_control.hpp"
#include "lights/spot_light.hpp"
#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "model_dynamics/airplane_dynamics.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"
#include "structs/airplane_parameters.hpp"

#include <glm/glm.hpp>

constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor { 1, 1, 1 };
constexpr float lightsCutoffInnerDeg = 8;
constexpr float lightsCutoffOuterDeg = 10;
constexpr glm::vec3 leftLightPosition { 2.14, -0.448, -1.096 };
constexpr glm::vec3 rightLightPosition { -2.14, -0.448, -1.096 };

Airplane::Airplane(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, const Mesh& capMesh, const Mesh& propellerMesh,
	const Mesh& bodyMesh, const Mesh& joinsMesh, const Mesh& tiresMesh, const Mesh& lightMesh,
	AirplaneParameters parameters) :
	Model { surfaceShaderProgram, lightShaderProgram },
	m_cap { capMesh },
	m_propeller { propellerMesh },
	m_body { bodyMesh },
	m_joins { joinsMesh },
	m_tires { tiresMesh },
	m_leftLight { surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
		lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
		lightsCutoffOuterDeg, m_matrix },
	m_rightLight { surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
		lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
		lightsCutoffOuterDeg, m_matrix },
	m_parameters { parameters },
	m_flightControl { parameters.controlSurfacesConstraints },
	m_dynamics { AirplaneDynamics { parameters, m_flightControl } }
{
	m_leftLight.translate(leftLightPosition, m_matrix);
	m_rightLight.translate(rightLightPosition, m_matrix);
	updateShaderLightMatrix();
}

void Airplane::update()
{
	setState(m_dynamics.computeNewState(getState()));
}

void Airplane::rotatePropeller(float angleDeg)
{
	m_propeller.roll(angleDeg);
}

void Airplane::updateShaderLightMatrix() const
{
	m_leftLight.updateShaderLightTranslation(m_matrix);
	m_rightLight.updateShaderLightTranslation(m_matrix);
}

void Airplane::renderSurfaces() const
{
	m_cap.render(m_matrix);
	m_propeller.render(m_matrix);
	m_body.render(m_matrix);
	m_joins.render(m_matrix);
	m_tires.render(m_matrix);
}

void Airplane::renderLights() const
{
	m_leftLight.render(m_matrix);
	m_rightLight.render(m_matrix);
}
