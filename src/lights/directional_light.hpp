#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "light.hpp"

class DirectionalLight : public Light {
	static unsigned int idCounter;
protected:
	virtual void updateShaderLightValues() const override;
public:
	DirectionalLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, glm::vec3 color);
	virtual void updateShaderLightModelMatrix(glm::mat4 modelMatrix) const override;

	virtual ~DirectionalLight() { }
};

#endif
