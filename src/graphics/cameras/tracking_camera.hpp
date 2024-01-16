#pragma once

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

namespace Graphics
{
	class TrackingCamera : public PerspectiveCamera
	{
	public:
		TrackingCamera(float fovRad, float nearPlane, float farPlane,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const ShaderProgram& hudShaderProgram, const Model& model);
		virtual void use(float aspectRatio) override;
		virtual ~TrackingCamera() = default;

	protected:
		const Model& m_model;

		void aimAtModel();
	};
};
