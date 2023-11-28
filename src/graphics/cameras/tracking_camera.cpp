#include "graphics/cameras/tracking_camera.hpp"

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Graphics
{
	TrackingCamera::TrackingCamera(float FoVDeg, float nearPlane, float farPlane,
		const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Model& model) :
		PerspectiveCamera{FoVDeg, nearPlane, farPlane, surfaceShaderProgram, lightShaderProgram},
		m_model{model}
	{ }

	void TrackingCamera::updateShaders(float aspectRatio)
	{
		aimAtModel();
		Camera::updateShaders(aspectRatio);
	}

	void TrackingCamera::aimAtModel()
	{
		Common::State state = getState();
		glm::vec3 modelPosition = m_model.getPosition();

		glm::vec3 direction = glm::normalize(state.position - modelPosition);

		glm::vec3 right = glm::normalize(glm::cross
		(
			glm::vec3{0, 1, 0},
			glm::vec3{direction}
		));

		glm::vec3 up = glm::normalize(glm::cross
		(
			glm::vec3{direction},
			glm::vec3{right}
		));

		// constructor takes arguments column-wise
		glm::mat3 orientationMatrix =
		{
			right.x, right.y, right.z,
			up.x, up.y, up.z,
			direction.x, direction.y, direction.z
		};

		state.orientation = glm::quat_cast(orientationMatrix);

		setState(state);
	}
};
