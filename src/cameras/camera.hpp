#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "movable.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

class Camera : public Movable
{
public:
	virtual void use(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);

protected:
	glm::mat4 m_projectionMatrix {};
	
	Camera(glm::mat4 projectionMatrix);
	void updateShaderMatrices(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) const;
	virtual glm::mat4 getOriginMatrix() const;
	virtual glm::mat4 getCameraMatrix() const final;
	virtual glm::vec3 getCameraPosition() const final;
	virtual glm::mat4 getViewMatrix() const final;
	virtual ~Camera() = default;

private:
	using Movable::scale;
};

#endif
