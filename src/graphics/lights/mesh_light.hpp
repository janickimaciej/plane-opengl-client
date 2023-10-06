#ifndef MESH_LIGHT_HPP
#define MESH_LIGHT_HPP

#include "graphics/lights/light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"

#include <glm/glm.hpp>

class MeshLight : public Light
{
public:
	void render(const glm::mat4& modelMatrix) const;

	void scale(float scaleRatio, const glm::mat4& modelMatrix); // locally
	void rotate(const glm::vec3& axis, float angleDeg, const glm::mat4& modelMatrix); // locally
	void translate(const glm::vec3& translation, const glm::mat4& modelMatrix);

	void pitch(float angleDeg, const glm::mat4& modelMatrix); // locally
	void yaw(float angleDeg, const glm::mat4& modelMatrix); // locally
	void roll(float angleDeg, const glm::mat4& modelMatrix); // locally
	void moveAlongZ(float distance, const glm::mat4& modelMatrix); // locally

protected:
	Submodel m_submodel;
	const ShaderProgram& m_surfaceShaderProgram;

	MeshLight(const ShaderProgram& surfaceShaderProgram, unsigned int id, const Mesh& mesh,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		const glm::vec3& color);
	virtual ~MeshLight() = default;
};

#endif
