#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "shader_program.hpp"

#include <glm/glm.hpp>

class Light
{
public:
	virtual void updateShaderLightTranslation(const glm::mat4& modelMatrix) const = 0;
	void setColor(const glm::vec3& color);

protected:
	const ShaderProgram& surfaceShaderProgram;
	unsigned int m_id{};
	float m_attenuationQuadratic{};
	float m_attenuationLinear{};
	float m_attenuationConstant{};
	glm::vec3 m_color{};

	Light(const ShaderProgram& surfaceShaderProgram, unsigned int id, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, const glm::vec3& color);
	virtual void updateShaderLightParameters() const = 0;
	virtual ~Light() = default;
};

#endif
