#include "graphics/submodel.hpp"

#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "transformable.hpp"

#include <glm/glm.hpp>

#include <memory>

Submodel::Submodel(const ShaderProgram& shaderProgram, const std::shared_ptr<const Mesh>& mesh,
	const Material& material, const std::shared_ptr<const Texture>& texture) :
	m_shaderProgram{shaderProgram},
	m_mesh{mesh},
	m_material{material},
	m_texture{texture}
{ }

void Submodel::render(const glm::mat4& modelMatrix) const
{
	updateShaderValues(modelMatrix * getMatrix());
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

glm::mat4 Submodel::getMatrix() const
{
	return Transformable::getMatrix();
}

void Submodel::updateShaderValues(const glm::mat4& modelSubmodelMatrix) const
{
	m_shaderProgram.setUniformMatrix4f("modelMeshMatrix", modelSubmodelMatrix);
	m_shaderProgram.setUniform3f("material.color", m_material.color);
	m_shaderProgram.setUniform1f("material.diffuse", m_material.diffuse);
	m_shaderProgram.setUniform1f("material.specular", m_material.specular);
	m_shaderProgram.setUniform1f("material.shininess", m_material.shininess);
	m_shaderProgram.setUniform1b("isTextureEnabled", (bool)m_texture);
}
