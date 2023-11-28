#pragma once

#include "common/transformable.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Graphics
{
	class Submodel : public Common::Transformable
	{
	public:
		Submodel(const ShaderProgram& shaderProgram, const std::shared_ptr<const Mesh>& mesh,
			const Material& material, const std::shared_ptr<const Texture>& texture = nullptr);
		void render(const glm::mat4& modelMatrix) const;
		void scale(float scaleRatio);
		glm::mat4 getMatrix() const;
		virtual ~Submodel() = default;
	
	private:
		const ShaderProgram& m_shaderProgram;
		const std::shared_ptr<const Mesh> m_mesh;
		const Material m_material;
		const std::shared_ptr<const Texture> m_texture;

		void updateShaders(const glm::mat4& modelSubmodelMatrix) const;
	};
};
