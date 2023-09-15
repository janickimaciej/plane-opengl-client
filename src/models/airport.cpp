#include "models/airport.hpp"

#include "lights/spot_light.hpp"
#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <vector>

constexpr std::size_t hangarsCount = 3;
constexpr std::size_t lightsCount = 8;
constexpr float lightsAttenuationQuadratic = 0.0001f;
constexpr float lightsAttenuationLinear = 0.0005f;
constexpr float lightsAttenuationConstant = 1;
constexpr glm::vec3 lightsColor{1, 1, 0.6};
constexpr float lightsCutoffInnerDeg = 25;
constexpr float lightsCutoffOuterDeg = 35;

Airport::Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
	const Mesh& groundMesh, const Mesh& runwayMesh, const Mesh& apronMesh, const Mesh& towerMesh,
	const Mesh& hangarMesh, const Mesh& lightBodyMesh, const Mesh& lightMesh) :
	Model{surfaceShaderProgram, lightShaderProgram},
	m_ground{groundMesh},
	m_runway{runwayMesh},
	m_apron{apronMesh},
	m_tower{towerMesh}
{
	for (std::size_t i = 0; i < hangarsCount; ++i)
	{
		m_hangars.push_back(MeshInstance{hangarMesh});

		constexpr float hangarsGapZ = 46;
		m_hangars[i].translate(glm::vec3{0, 0, -hangarsGapZ*(int)i});
	}

	for (std::size_t i = 0; i < lightsCount; ++i)
	{
		m_lightBodies.push_back(MeshInstance{lightBodyMesh});
		m_lights.push_back(SpotLight{surfaceShaderProgram, lightMesh, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg,
			lightsCutoffOuterDeg, getMatrix()});

		constexpr float firstLightPositionX = -49;
		constexpr float lightsGapX = 14;
		constexpr float lightsPositionY = 7;
		constexpr float lightsPositionZ = 250;
		glm::vec3 lightPosition{firstLightPositionX + lightsGapX*(int)i, lightsPositionY,
			lightsPositionZ};
		m_lightBodies[i].translate(lightPosition);
		m_lights[i].translate(lightPosition, getMatrix());

		constexpr float lightsRotationYaw = 180;
		m_lightBodies[i].rotateYaw(lightsRotationYaw);
		m_lights[i].yaw(lightsRotationYaw, getMatrix());

		constexpr float lightsRotationPitch = 15;
		m_lightBodies[i].rotatePitch(lightsRotationPitch);
		m_lights[i].pitch(lightsRotationPitch, getMatrix());
	}

	updateShaderLightMatrix();
}

void Airport::updateShaderLightMatrix() const
{
	for (const SpotLight& light : m_lights)
	{
		light.updateShaderLightTranslation(getMatrix());
	}
}

void Airport::renderSurfaces() const
{
	m_ground.render(getMatrix());
	m_runway.render(getMatrix());
	m_apron.render(getMatrix());
	m_tower.render(getMatrix());
	for (const MeshInstance& hangar : m_hangars)
	{
		hangar.render(getMatrix());
	}
	for (const MeshInstance& lightBody : m_lightBodies)
	{
		lightBody.render(getMatrix());
	}
}

void Airport::renderLights() const
{
	for (const SpotLight& light : m_lights)
	{
		light.render(getMatrix());
	}
}
