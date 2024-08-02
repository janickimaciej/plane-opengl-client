#pragma once

#include "common/transformable.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Camera : public Common::Transformable
	{
	public:
		virtual void updateProjectionMatrix() = 0;
		virtual void use(float aspectRatio);
		virtual ~Camera() = default;

	protected:
		glm::mat4 m_projectionMatrix{};
		float m_aspectRatio{};
		const float m_nearPlane{};
		const float m_farPlane{};

		const ShaderProgram& m_surfaceShaderProgram;
		const ShaderProgram& m_lightShaderProgram;
		const ShaderProgram& m_hudShaderProgram;
	
		Camera(float nearPlane, float farPlane, const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram, const ShaderProgram& hudShaderProgram);
		virtual glm::mat4 getCameraMatrix() const;
		glm::vec3 getCameraPosition() const;
		glm::mat4 getViewMatrix() const;
	};
};
