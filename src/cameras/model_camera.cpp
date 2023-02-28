#include "model_camera.hpp"

glm::mat4 ModelCamera::getOriginMatrix() const {
	return model.getModelMatrix();
}

ModelCamera::ModelCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane, const Model& model) :
	PerspectiveCamera(FoVDeg, aspectRatio, nearPlane, farPlane), model(model) { }
