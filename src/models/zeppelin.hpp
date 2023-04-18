#ifndef ZEPPELIN
#define ZEPPELIN

#include "model.hpp"

class Zeppelin : public Model {
	MeshInstance body;

	virtual void updateShaderLightModelMatrix() const override;
	virtual void renderSurfaces() const override;
	virtual void renderLights() const override;
public:
	Zeppelin(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		const Mesh& bodyMesh);
	
	virtual ~Zeppelin() { }
};

#endif
