#include "graphics/submodels/light_submodel.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>

namespace Graphics
{
	LightSubmodel::LightSubmodel(const Light& light, const ShaderProgram& shaderProgram,
		const std::shared_ptr<const Mesh>& mesh, const Material& material,
		const std::shared_ptr<const Texture>& texture) :
		Submodel{shaderProgram, mesh, material, texture},
		m_light{light}
	{ }

	LightSubmodel::LightSubmodel(const Light& light, const LightSubmodel& lightSubmodel) :
		Submodel{lightSubmodel},
		m_light{light}
	{ }
	
	glm::mat4 LightSubmodel::getSubmodelMatrix() const
	{
		return m_light.getState().matrix() * getMatrix();
	}
};
