#pragma once

#include "common/transformable.hpp"
#include "common/state.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Model : public Common::Transformable
	{
	public:
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
	
		Model(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram);
		virtual void renderSurfaces() const = 0;
		virtual void renderLights() const = 0;
	};
};
