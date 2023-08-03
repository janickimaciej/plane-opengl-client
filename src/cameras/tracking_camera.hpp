#ifndef TRACKING_CAMERA_HPP
#define TRACKING_CAMERA_HPP

#include "cameras/perspective_camera.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

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
