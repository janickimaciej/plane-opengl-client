#ifndef MODEL_CAMERA_HPP
#define MODEL_CAMERA_HPP

#include "cameras/perspective_camera.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

class ModelCamera : public PerspectiveCamera
{
public:
	ModelCamera(float FoVDeg, float aspectRatio, float nearPlane, float farPlane,
		const Model& model);
	virtual ~ModelCamera() = default;

protected:
	const Model& m_model;

	virtual glm::mat4 getOriginMatrix() const override;
};

#endif
