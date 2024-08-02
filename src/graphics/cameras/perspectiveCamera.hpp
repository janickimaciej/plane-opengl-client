#pragma once

#include "graphics/cameras/camera.hpp"
#include "graphics/shaderProgram.hpp"

namespace Graphics
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fovRad, float nearPlane, float farPlane,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const ShaderProgram& hudShaderProgram);
		virtual void updateProjectionMatrix() override;
		virtual ~PerspectiveCamera() = default;

	private:
		float m_fovRad{};
	};
};
