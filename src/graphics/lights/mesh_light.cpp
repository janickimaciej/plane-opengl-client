#include "graphics/lights/mesh_light.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	void MeshLight::render(const glm::mat4& modelMatrix) const
	{
		m_submodel.render(modelMatrix);
	}

	void MeshLight::scale(float scaleRatio)
	{
		m_submodel.scale(scaleRatio);
	}

	void MeshLight::rotate(const glm::vec3& axis, float angleDeg)
	{
		m_submodel.rotate(axis, angleDeg);
	}

	void MeshLight::translate(const glm::vec3& translation)
	{
		m_submodel.translate(translation);
	}

	void MeshLight::pitch(float angleDeg)
	{
		m_submodel.rotatePitch(angleDeg);
	}

	void MeshLight::yaw(float angleDeg)
	{
		m_submodel.rotateYaw(angleDeg);
	}

	void MeshLight::roll(float angleDeg)
	{
		m_submodel.rotateRoll(angleDeg);
	}

	void MeshLight::moveAlongZ(float distance)
	{
		m_submodel.moveZ(distance);
	}

	MeshLight::MeshLight(unsigned int id, const ShaderProgram& surfaceShaderProgram,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		const glm::vec3& color, const Submodel& submodel) :
		Light{id, surfaceShaderProgram, attenuationQuadratic, attenuationLinear,
			attenuationConstant, color},
		m_submodel{submodel}
	{ }
};
