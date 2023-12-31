#pragma once

#include "common/transformable.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
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
		Submodel(const Submodel& submodel);
		Submodel(Submodel&& submodel) noexcept;
		void render(const glm::mat4& modelMatrix) const;
		void scale(float scaleRatio);
		void mirrorX();
		void mirrorY();
		void mirrorZ();
		virtual glm::mat4 getSubmodelMatrix() const;
		void setMaterial(const Material& material);
		virtual ~Submodel() = default;
	
	private:
		const ShaderProgram& m_shaderProgram;
		const std::shared_ptr<const Mesh> m_mesh;
		Material m_material;
		const std::shared_ptr<const Texture> m_texture;

		void updateShaders(const glm::mat4& modelSubmodelMatrix) const;
	};
};
