#pragma once

#include "graphics/lights/directionalLight.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class DirectionalLightModel : public Model
	{
	public:
		DirectionalLightModel(const ShaderProgram& surfaceShaderProgram,
			const glm::vec3& lightColor);
		void setLightColor(const glm::vec3& color);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~DirectionalLightModel() = default;

	private:
		DirectionalLight m_light;
	};
};
