#ifndef LIGHT
#define LIGHT

#include <glm/glm.hpp>
#include "../shader_program.hpp"

class Light {
protected:
	const ShaderProgram& surfaceShaderProgram;
	unsigned int id;
	float attenuationQuadratic;
	float attenuationLinear;
	float attenuationConstant;
	glm::vec3 color;

	Light(const ShaderProgram& surfaceShaderProgram, unsigned int id, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, glm::vec3 color);
	virtual void updateShaderLightParameters() const = 0;
	virtual ~Light() = default;
public:
	virtual void updateShaderLightTranslation(glm::mat4 modelMatrix) const = 0;
	void setColor(glm::vec3 color);
};

#endif
