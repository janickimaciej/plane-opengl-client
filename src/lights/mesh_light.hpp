#ifndef MESH_LIGHT
#define MESH_LIGHT

#include "light.hpp"
#include "../mesh_instance.hpp"
#include <glm/glm.hpp>
#include "../shader_program.hpp"

class MeshLight : public Light {
protected:
	MeshInstance meshInstance;
	const ShaderProgram& surfaceShaderProgram;

	MeshLight(const ShaderProgram& surfaceShaderProgram, unsigned int id, const Mesh& mesh,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant, glm::vec3 color);
	virtual ~MeshLight() = default;
public:
	void render(glm::mat4 modelMatrix) const;

	void scale(float scaleRatio, glm::mat4 modelMatrix); // locally
	void rotate(glm::vec3 axis, float angleDeg, glm::mat4 modelMatrix); // locally
	void translate(glm::vec3 translation, glm::mat4 modelMatrix);

	void pitch(float angleDeg, glm::mat4 modelMatrix); // locally
	void yaw(float angleDeg, glm::mat4 modelMatrix); // locally
	void roll(float angleDeg, glm::mat4 modelMatrix); // locally
	void moveAlongZ(float distance, glm::mat4 modelMatrix); // locally
};

#endif
