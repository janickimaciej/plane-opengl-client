#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "transformable.hpp"
#include "state.hpp"

#include <glm/glm.hpp>

class Model : public Transformable
{
public:
	void tryInitializing();
	virtual void initialize() = 0;
	virtual void updateShaders() = 0;
	void render() const;
	glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;
	virtual void scale(float scaleRatio) override; // locally
	virtual ~Model() = default;

protected:
	bool isInitialized = false;

	const ShaderProgram& m_surfaceShaderProgram;
	const ShaderProgram& m_lightShaderProgram;

	AssetManager<const Mesh>& m_meshManager;
	AssetManager<const Texture>& m_textureManager;
	
	Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager);
	virtual void renderSurfaces() const = 0;
	virtual void renderLights() const = 0;
};
