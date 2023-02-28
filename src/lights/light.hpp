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
	virtual void updateShaderLightValues() const = 0;
public:
	virtual void updateShaderLightModelMatrix(glm::mat4 modelMatrix) const = 0;

	void setColor(glm::vec3 color);

	virtual ~Light() { }
};

#endif
