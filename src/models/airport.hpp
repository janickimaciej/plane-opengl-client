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

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
public:
	Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& groundMesh, const Mesh& runwayMesh, const Mesh& apronMesh, const Mesh& towerMesh,
		const Mesh& hangarMesh, const Mesh& lightBodyMesh, const Mesh& lightMesh);
	virtual ~Airport() = default;
};

#endif
