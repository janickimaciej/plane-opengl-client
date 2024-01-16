#include "graphics/cameras/tracking_camera.hpp"

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Graphics
{
	TrackingCamera::TrackingCamera(float fovRad, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const ShaderProgram& hudShaderProgram, const Model& model) :
		PerspectiveCamera{fovRad, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram,
			hudShaderProgram},
		m_model{model}
	{ }

	void TrackingCamera::use(float aspectRatio)
	{
		aimAtModel();
		Camera::use(aspectRatio);
	}

	void TrackingCamera::aimAtModel()
	{
		Common::State state = getState();
		glm::vec3 modelPosition = m_model.getPosition();
		state.setOrientation(glm::normalize(state.position - modelPosition));
		setState(state);
	}
};
