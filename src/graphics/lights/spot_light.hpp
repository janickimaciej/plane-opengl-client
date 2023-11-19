#pragma once

#include "graphics/lights/mesh_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"

#include <glm/glm.hpp>

class SpotLight : public MeshLight
{
public:
	SpotLight(const ShaderProgram& surfaceShaderProgram, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, const glm::vec3& color,
		float cutoffInnerDeg, float cutoffOuterDeg, const Submodel& submodel);
	virtual void updateShaders(const glm::mat4& modelMatrix) const override;
	virtual ~SpotLight() = default;

protected:
	float m_cutoffInnerDeg{};
	float m_cutoffOuterDeg{};

private:
	static unsigned int s_idCounter;
};
