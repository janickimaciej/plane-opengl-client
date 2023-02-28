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
		Mesh& capMesh, Mesh& propellerMesh, Mesh& bodyMesh, Mesh& joinsMesh, Mesh& tiresMesh, Mesh& lightMesh);
	void rotatePropeller(float angleDeg);

	virtual ~Airplane() { }
};

#endif
