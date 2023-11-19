#pragma once

#include "graphics/lights/directional_light.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

#include <glm/glm.hpp>

#include <memory>

class DirectionalLightModel : public Model
{
public:
	DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
		AssetManager<const Texture>& textureManager, const glm::vec3& lightColor);
	virtual void initialize() override;
	void setLightColor(const glm::vec3& color);
	virtual void updateShaders() override;
	virtual ~DirectionalLightModel() = default;

private:
	glm::vec3 m_lightColor{};

	std::unique_ptr<DirectionalLight> m_light;

	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};
