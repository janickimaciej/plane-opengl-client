#include "lights/mesh_light.hpp"

#include "lights/light.hpp"
#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

void MeshLight::render(const glm::mat4& modelMatrix) const
{
	m_meshInstance.render(modelMatrix);
}

void MeshLight::scale(float scaleRatio, const glm::mat4& modelMatrix)
{
	m_meshInstance.scale(scaleRatio);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::rotate(const glm::vec3& axis, float angleDeg, const glm::mat4& modelMatrix)
{
	m_meshInstance.rotate(axis, angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::translate(const glm::vec3& translation, const glm::mat4& modelMatrix)
{
	m_meshInstance.translate(translation);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::pitch(float angleDeg, const glm::mat4& modelMatrix)
{
	m_meshInstance.pitch(angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::yaw(float angleDeg, const glm::mat4& modelMatrix)
{
	m_meshInstance.yaw(angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::roll(float angleDeg, const glm::mat4& modelMatrix)
{
	m_meshInstance.roll(angleDeg);
	updateShaderLightTranslation(modelMatrix);
}

void MeshLight::moveAlongZ(float distance, const glm::mat4& modelMatrix)
{
	m_meshInstance.moveAlongZ(distance);
	updateShaderLightTranslation(modelMatrix);
}

MeshLight::MeshLight(const ShaderProgram& surfaceShaderProgram, unsigned int id, const Mesh& mesh,
	float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
	const glm::vec3& color) :
	Light{surfaceShaderProgram, id, attenuationQuadratic, attenuationLinear, attenuationConstant,
		color},
	m_meshInstance{mesh},
	m_surfaceShaderProgram{surfaceShaderProgram}
{ }
