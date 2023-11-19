#pragma once

#include "graphics/lights/light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"

#include <glm/glm.hpp>

class MeshLight : public Light
{
public:
	void render(const glm::mat4& modelMatrix) const;

	void scale(float scaleRatio); // locally
	void rotate(const glm::vec3& axis, float angleDeg); // locally
	void translate(const glm::vec3& translation);

	void pitch(float angleDeg); // locally
	void yaw(float angleDeg); // locally
	void roll(float angleDeg); // locally
	void moveAlongZ(float distance); // locally

	virtual ~MeshLight() = default;

protected:
	Submodel m_submodel;

	MeshLight(unsigned int id, const ShaderProgram& surfaceShaderProgram,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		const glm::vec3& color, const Submodel& submodel);
};
