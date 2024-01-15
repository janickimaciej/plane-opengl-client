#pragma once

#include "common/transformable.hpp"
#include "common/state.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Model : public Common::Transformable
	{
	public:
		virtual void updateShaders() = 0;
		virtual void render() const = 0;
		glm::mat4 getModelMatrix() const;
		glm::vec3 getPosition() const;
		virtual void scale(float scaleRatio) override; // locally
		virtual ~Model() = default;
	};
};
