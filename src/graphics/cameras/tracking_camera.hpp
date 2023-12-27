#pragma once

#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"

namespace Graphics
{
	class TrackingCamera : public PerspectiveCamera
	{
	public:
		TrackingCamera(float FoVRad, float nearPlane, float farPlane,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const Model& model);
		virtual void updateShaders(float aspectRatio) override;
		virtual ~TrackingCamera() = default;

	protected:
		const Model& m_model;

		void aimAtModel();
	};
};
