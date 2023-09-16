#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/mesh_instance.hpp"
#include "graphics/shader_program.hpp"
#include "models/model.hpp"

#include <vector>

class Airport : public Model
{
public:
	Airport(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& groundMesh, const Mesh& runwayMesh, const Mesh& apronMesh,
		const Mesh& towerMesh, const Mesh& hangarMesh, const Mesh& lightBodyMesh,
		const Mesh& lightMesh);
	virtual ~Airport() = default;

private:
	MeshInstance m_ground;
	MeshInstance m_runway;
	MeshInstance m_apron;
	MeshInstance m_tower;
	std::vector<MeshInstance> m_hangars{};
	std::vector<MeshInstance> m_lightBodies{};
	std::vector<SpotLight> m_lights{};

	virtual void updateShaderLightMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
};

#endif
