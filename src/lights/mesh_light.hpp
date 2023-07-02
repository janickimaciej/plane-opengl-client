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
	virtual void updateShaderLightMeshMatrix() const = 0;
	virtual ~MeshLight() = default;
public:
	void render() const;

	void scale(float scaleRatio); // locally
	void rotate(glm::vec3 axis, float angleDeg); // locally
	void translate(glm::vec3 translation);

	void pitch(float angleDeg); // locally
	void yaw(float angleDeg); // locally
	void roll(float angleDeg); // locally
	void moveAlongZ(float distance); // locally
};

#endif
