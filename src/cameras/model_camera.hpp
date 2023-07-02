#ifndef MODEL_CAMERA
#define MODEL_CAMERA

#include <glm/glm.hpp>
#include "perspective_camera.hpp"
#include "../models/model.hpp"

class ModelCamera : public PerspectiveCamera {
protected:
	const Model& model;

	virtual glm::mat4 getOriginMatrix() const override;
public:
	ModelCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane, const Model& model);
	virtual ~ModelCamera() = default;
};

#endif
