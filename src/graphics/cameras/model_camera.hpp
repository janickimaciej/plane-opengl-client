#pragma once

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class ModelCamera : public PerspectiveCamera
	{
	public:
		ModelCamera(const Model& model, float FoVRad, float nearPlane, float farPlane,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);
		virtual ~ModelCamera() = default;

	protected:
		const Model& m_model;

		virtual glm::mat4 getCameraMatrix() const override;
	};
};
