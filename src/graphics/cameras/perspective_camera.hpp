#pragma once

#include "graphics/cameras/camera.hpp"
#include "graphics/shader_program.hpp"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float FoVDeg, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);
	virtual void updateProjectionMatrix() override;
	virtual ~PerspectiveCamera() = default;
};
