#ifndef MESH_LIGHT_HPP
#define MESH_LIGHT_HPP

#include "lights/light.hpp"
#include "mesh.hpp"
#include "mesh_instance.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

class MeshLight : public Light
{
public:
	void render(glm::mat4 modelMatrix) const;

	void scale(float scaleRatio, glm::mat4 modelMatrix); // locally
	void rotate(glm::vec3 axis, float angleDeg, glm::mat4 modelMatrix); // locally
	void translate(glm::vec3 translation, glm::mat4 modelMatrix);

	void pitch(float angleDeg, glm::mat4 modelMatrix); // locally
	void yaw(float angleDeg, glm::mat4 modelMatrix); // locally
	void roll(float angleDeg, glm::mat4 modelMatrix); // locally
	void moveAlongZ(float distance, glm::mat4 modelMatrix); // locally

protected:
	MeshInstance m_meshInstance;
	const ShaderProgram& m_surfaceShaderProgram;

	MeshLight(const ShaderProgram& surfaceShaderProgram, unsigned int id, const Mesh& mesh,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		glm::vec3 color);
	virtual ~MeshLight() = default;
};

#endif
