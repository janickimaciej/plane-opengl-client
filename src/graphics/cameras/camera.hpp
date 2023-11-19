#pragma once

#include "graphics/shader_program.hpp"
#include "transformable.hpp"

#include <glm/glm.hpp>

class Camera : public Transformable
{
public:
	virtual void updateProjectionMatrix() = 0;
	virtual void use(float aspectRatio);

protected:
	glm::mat4 m_projectionMatrix{};
	const float m_FoVDeg{};
	float m_aspectRatio{};
	const float m_nearPlane{};
	const float m_farPlane{};

	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;
	
	Camera(float FoVDeg, float nearPlane, float farPlane, const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram);
	void updateShaderMatrices(float aspectRatio);
	virtual glm::mat4 getOriginMatrix() const;
	glm::mat4 getCameraMatrix() const;
	glm::vec3 getCameraPosition() const;
	glm::mat4 getViewMatrix() const;
	virtual ~Camera() = default;
};
