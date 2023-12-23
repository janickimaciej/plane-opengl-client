#pragma once

#include "graphics/lights/light.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>

namespace Graphics
{
	class LightSubmodel : public Submodel
	{
	public:
		LightSubmodel(const Light& light, const ShaderProgram& shaderProgram,
			const std::shared_ptr<const Mesh>& mesh, const Material& material,
			const std::shared_ptr<const Texture>& texture = nullptr);
		LightSubmodel(const Light& light, const LightSubmodel& lightSubmodel);
		virtual glm::mat4 getSubmodelMatrix() const override;
		virtual ~LightSubmodel() = default;

	private:
		const Light& m_light;
	};
};
