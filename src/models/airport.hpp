#ifndef AIRPORT
#define AIRPORT

#include <vector>
#include "model.hpp"
#include "../mesh_instance.hpp"
#include "../lights/spot_light.hpp"

class Airport : public Model {
	MeshInstance ground;
	MeshInstance runway;
	MeshInstance apron;
	MeshInstance tower;
	std::vector<MeshInstance> hangars;
	std::vector<MeshInstance> lightBodies;
	std::vector<SpotLight> lights;

	virtual void updateShaderLightModelMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
public:
	Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		Mesh& groundMesh, Mesh& runwayMesh, Mesh& apronMesh, Mesh& towerMesh, Mesh& hangarMesh,
		Mesh& lightBodyMesh, Mesh& lightMesh);
};

#endif
