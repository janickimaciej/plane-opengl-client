#ifndef AIRPLANE
#define AIRPLANE

#include "model.hpp"
#include "../mesh_instance.hpp"
#include "../lights/spot_light.hpp"
#include "../shader_program.hpp"

class Airplane : public Model {
	MeshInstance cap;
	MeshInstance propeller;
	MeshInstance body;
	MeshInstance joins;
	MeshInstance tires;
	SpotLight leftLight;
	SpotLight rightLight;

	virtual void updateShaderLightModelMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
public:
	Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& capMesh, const Mesh& propellerMesh, const Mesh& bodyMesh, const Mesh& joinsMesh,
		const Mesh& tiresMesh, const Mesh& lightMesh);
	void rotatePropeller(float angleDeg);
	virtual ~Airplane() = default;
};

#endif
