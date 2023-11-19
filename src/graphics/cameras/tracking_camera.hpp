#pragma once

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

class TrackingCamera : public PerspectiveCamera
{
public:
	TrackingCamera(float FoVDeg, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Model& model);
	virtual void updateShaders(float aspectRatio) override;
	virtual ~TrackingCamera() = default;

protected:
	const Model& m_model;

	void aimAtModel();
};
