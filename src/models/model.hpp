#ifndef MODEL
#define MODEL

#include "../movable.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "../shader_program.hpp"
#include "../mesh_instance.hpp"

class Model : public Movable {
protected:
	const ShaderProgram& surfaceShaderProgram;
	const ShaderProgram& lightShaderProgram;

	void updateShaderValues() const;
	virtual void updateShaderLightModelMatrix() const = 0;
	virtual void renderSurfaces() const = 0;
	virtual void renderLights() const = 0;
	Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);
public:
	void render() const;
	glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;

	virtual void scale(float scaleRatio) override; // locally
	virtual void rotate(glm::vec3 axis, float angleDeg) override; // locally
	virtual void translate(glm::vec3 translation) override;

	virtual void pitch(float angleDeg) override; // locally
	virtual void yaw(float angleDeg) override; // locally
	virtual void roll(float angleDeg) override; // locally
	virtual void moveAlongZ(float distance) override; // locally

	virtual ~Model() { }
};

#endif
