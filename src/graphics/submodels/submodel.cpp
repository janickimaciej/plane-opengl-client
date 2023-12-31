#include "graphics/submodels/submodel.hpp"

#include "common/transformable.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Graphics
{
	Submodel::Submodel(const ShaderProgram& shaderProgram, const std::shared_ptr<const Mesh>& mesh,
		const Material& material, const std::shared_ptr<const Texture>& texture) :
		m_shaderProgram{shaderProgram},
		m_mesh{mesh},
		m_material{material},
		m_texture{texture}
	{ }

	Submodel::Submodel(const Submodel& submodel) :
		Transformable{submodel},
		m_shaderProgram{submodel.m_shaderProgram},
		m_mesh{submodel.m_mesh},
		m_material{submodel.m_material},
		m_texture{submodel.m_texture}
	{ }

	Submodel::Submodel(Submodel&& submodel) noexcept :
		Transformable{submodel},
		m_shaderProgram{submodel.m_shaderProgram},
		m_mesh{submodel.m_mesh},
		m_material{submodel.m_material},
		m_texture{submodel.m_texture}
	{ }

	void Submodel::render(const glm::mat4& modelMatrix) const
	{
		updateShaders(modelMatrix * getSubmodelMatrix());
		if (m_texture)
		{
			m_texture->use();
		}
		m_mesh->render();
	}

	void Submodel::scale(float scaleRatio)
	{
		Transformable::scale(scaleRatio);
	}

	void Submodel::mirrorX()
	{
		Transformable::mirrorX();
	}

	void Submodel::mirrorY()
	{
		Transformable::mirrorY();
	}

	void Submodel::mirrorZ()
	{
		Transformable::mirrorZ();
	}

	glm::mat4 Submodel::getSubmodelMatrix() const
	{
		return getMatrix();
	}
	
	void Submodel::setMaterial(const Material& material)
	{
		m_material = material;
	}

	void Submodel::updateShaders(const glm::mat4& modelSubmodelMatrix) const
	{
		m_shaderProgram.setUniformMatrix4f("modelSubmodelMatrix", modelSubmodelMatrix);
		m_shaderProgram.setUniform3f("material.color", m_material.color);
		m_shaderProgram.setUniform1f("material.diffuse", m_material.diffuse);
		m_shaderProgram.setUniform1f("material.specular", m_material.specular);
		m_shaderProgram.setUniform1f("material.shininess", m_material.shininess);
		m_shaderProgram.setUniform1b("material.isMetal", m_material.isMetal);
		m_shaderProgram.setUniform1b("isTextureEnabled", static_cast<bool>(m_texture));
	}
};
