#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "lights/mesh_light.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

#include <glm/glm.hpp>

class SpotLight : public MeshLight
{
public:
	SpotLight(const ShaderProgram& surfaceShaderProgram, const Mesh& mesh,
		float attenuationQuadratic, float attenuationLinear, float attenuationConstant,
		const glm::vec3& color, float cutoffInnerDeg, float cutoffOuterDeg,
		const glm::mat4& modelMatrix);
	virtual void updateShaderLightTranslation(const glm::mat4& modelMatrix) const override;
	virtual ~SpotLight() = default;

protected:
	float m_cutoffInnerDeg {};
	float m_cutoffOuterDeg {};

	virtual void updateShaderLightParameters() const override;

private:
	static unsigned int s_idCounter;
};

#endif
