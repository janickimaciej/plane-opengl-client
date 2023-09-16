#ifndef TRACKING_CAMERA_HPP
#define TRACKING_CAMERA_HPP

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

class TrackingCamera : public PerspectiveCamera
{
public:
	TrackingCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
		const Model& model);
	virtual void use(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) override;
	virtual ~TrackingCamera() = default;

protected:
	const Model& m_model;

	void aimAtModel();
};

#endif
