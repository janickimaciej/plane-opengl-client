#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "graphics/lights/light.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

class DirectionalLight : public Light
{
public:
	DirectionalLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, const glm::vec3& color);
	virtual void updateShaderLightTranslation(const glm::mat4& modelMatrix) const override;
	virtual ~DirectionalLight() = default;

protected:
	virtual void updateShaderLightParams() const override;

private:
	static unsigned int s_idCounter;
};

#endif
