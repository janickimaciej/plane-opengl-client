#pragma once

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class ModelCamera : public PerspectiveCamera
	{
	public:
		ModelCamera(const Model& model, float fovRad, float nearPlane, float farPlane,
			const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			const ShaderProgram& hudShaderProgram);
		virtual ~ModelCamera() = default;

	protected:
		const Model& m_model;

		virtual glm::mat4 getCameraMatrix() const override;
	};
};
