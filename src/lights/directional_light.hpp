#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "lights/light.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

class DirectionalLight : public Light
{
public:
	DirectionalLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, const glm::vec3& color);
	virtual void updateShaderLightTranslation(const glm::mat4& modelMatrix) const override;
	virtual ~DirectionalLight() = default;

protected:
	virtual void updateShaderLightParameters() const override;

private:
	static unsigned int s_idCounter;
};

#endif
