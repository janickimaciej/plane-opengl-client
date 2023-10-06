#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "graphics/shader_program.hpp"
#include "transformable.hpp"

#include <glm/glm.hpp>

class Camera : public Transformable
{
public:
	virtual void use(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);

protected:
	glm::mat4 m_projectionMatrix{};
	
	Camera(const glm::mat4& projectionMatrix);
	void updateShaderMatrices(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) const;
	virtual glm::mat4 getOriginMatrix() const;
	virtual glm::mat4 getCameraMatrix() const final;
	virtual glm::vec3 getCameraPosition() const final;
	virtual glm::mat4 getViewMatrix() const final;
	virtual ~Camera() = default;
};

#endif
