#ifndef DIRECTIONAL_LIGHT_MODEL
#define DIRECTIONAL_LIGHT_MODEL

#include "model.hpp"
#include "../lights/directional_light.hpp"

class DirectionalLightModel : public Model {
	DirectionalLight light;

	virtual void updateShaderLightModelMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
public:
	DirectionalLightModel(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		glm::vec3 lightColor);

	void setLightColor(glm::vec3 color);

	virtual ~DirectionalLightModel() { }
};

#endif
