#ifndef TRACKING_CAMERA
#define TRACKING_CAMERA

#include "perspective_camera.hpp"
#include "../models/model.hpp"

class TrackingCamera : public PerspectiveCamera {
protected:
	const Model& model;
	void aimAtModel();
public:
	TrackingCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
		const Model& model);
	virtual void use(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram) override;
	virtual ~TrackingCamera() = default;
};

#endif
