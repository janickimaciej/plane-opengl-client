#pragma once

#include "graphics/lights/directional_light.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

class DirectionalLightModel : public Model
{
public:
	DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, const glm::vec3& lightColor);
	void setLightColor(const glm::vec3& color);
	virtual ~DirectionalLightModel() = default;

private:
	DirectionalLight m_light;

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};
