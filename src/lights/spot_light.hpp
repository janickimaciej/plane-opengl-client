#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "mesh_light.hpp"
#include <glm/glm.hpp>
#include "../shader_program.hpp"

class SpotLight : public MeshLight {
	static unsigned int idCounter;
protected:
	float cutoffInnerDeg;
	float cutoffOuterDeg;
	virtual void updateShaderLightParameters() const override;
public:
	SpotLight(const ShaderProgram& surfaceShaderProgram, const Mesh& mesh, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, glm::vec3 color, float cutoffInnerDeg,
		float cutoffOuterDeg, glm::mat4 modelMatrix);
	virtual void updateShaderLightTranslation(glm::mat4 modelMatrix) const override;
	virtual ~SpotLight() = default;
};

#endif
