#ifndef DIRECTIONAL_LIGHT_MODEL_HPP
#define DIRECTIONAL_LIGHT_MODEL_HPP

#include "lights/directional_light.hpp"
#include "models/model.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

class DirectionalLightModel : public Model
{
public:
	DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, glm::vec3 lightColor);
	void setLightColor(glm::vec3 color);
	virtual ~DirectionalLightModel() = default;

private:
	DirectionalLight m_light;

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};

#endif
