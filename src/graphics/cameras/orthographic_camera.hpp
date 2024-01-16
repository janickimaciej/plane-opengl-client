#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float width, float nearPlane, float farPlane,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const ShaderProgram& hudShaderProgram);
		virtual void updateProjectionMatrix() override;
		virtual ~OrthographicCamera() = default;

	private:
		float m_width{};
	};
};
