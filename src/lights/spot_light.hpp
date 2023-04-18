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
	virtual void updateShaderLightValues() const override;
	virtual void updateShaderLightMeshMatrix() const override;
public:
	SpotLight(const ShaderProgram& surfaceShaderProgram, const Mesh& mesh, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, glm::vec3 color, float cutoffInnerDeg,
		float cutoffOuterDeg);
	virtual void updateShaderLightModelMatrix(glm::mat4 modelMatrix) const override;

	virtual ~SpotLight() { }
};

#endif
