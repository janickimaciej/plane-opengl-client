#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include "../movable.hpp"
#include "../shader_program.hpp"

class Camera : public Movable {
	using Movable::scale;
protected:
	glm::mat4 projectionMatrix;

	void updateShaderMatrices(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) const;
	virtual glm::mat4 getOriginMatrix() const;
	virtual glm::mat4 getCameraMatrix() const final;
	virtual glm::vec3 getCameraPosition() const final;
	virtual glm::mat4 getViewMatrix() const final;
	Camera(glm::mat4 projectionMatrix);
public:
	virtual void use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);

	virtual ~Camera() { }
};

#endif
