#include "models/airport.hpp"

#include "lights/spot_light.hpp"
#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

#include <vector>

constexpr unsigned int hangarsCount = 3;
constexpr unsigned int lightsCount = 8;
constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor { 1, 1, 0.6 };
constexpr float lightsCutoffInnerDeg = 25;
constexpr float lightsCutoffOuterDeg = 35;

Airport::Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Mesh& groundMesh, const Mesh& runwayMesh, const Mesh& apronMesh, const Mesh& towerMesh,
	const Mesh& hangarMesh, const Mesh& lightBodyMesh, const Mesh& lightMesh) :
	Model { surfaceShaderProgram, lightShaderProgram },
	m_ground { groundMesh },
	m_runway { runwayMesh },
	m_apron { apronMesh },
	m_tower { towerMesh }
{
	for (size_t i = 0; i < hangarsCount; ++i)
	{
		m_hangars.push_back(MeshInstance { hangarMesh });
		m_hangars[i].translate(glm::vec3 { 0, 0, -46*i });
	}
	for (size_t i = 0; i < lightsCount; ++i)
	{
		glm::vec3 lightTranslation { -49 + 14*i, 7, 250 };

		m_lightBodies.push_back(MeshInstance { lightBodyMesh });
		m_lightBodies[i].translate(lightTranslation);
		m_lightBodies[i].yaw(180);
		m_lightBodies[i].pitch(15);

		m_lights.push_back(SpotLight { surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
			lightsCutoffOuterDeg, m_matrix });
		m_lights[i].translate(lightTranslation, m_matrix);
		m_lights[i].yaw(180, m_matrix);
		m_lights[i].pitch(15, m_matrix);
	}
	updateShaderLightMatrix();
}

void Airport::updateShaderLightMatrix() const
{
	for (size_t i = 0; i < lightsCount; ++i)
	{
		m_lights[i].updateShaderLightTranslation(m_matrix);
	}
}

void Airport::renderSurfaces() const
{
	m_ground.render(m_matrix);
	m_runway.render(m_matrix);
	m_apron.render(m_matrix);
	m_tower.render(m_matrix);
	for (size_t i = 0; i < hangarsCount; ++i)
	{
		m_hangars[i].render(m_matrix);
	}
	for (size_t i = 0; i < lightsCount; ++i)
	{
		m_lightBodies[i].render(m_matrix);
	}
}

void Airport::renderLights() const
{
	for (size_t i = 0; i < lightsCount; ++i)
	{
		m_lights[i].render(m_matrix);
	}
}
