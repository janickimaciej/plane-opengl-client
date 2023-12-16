#pragma once

#include "common/airplane_ctrl.hpp"
#include "graphics/airplane_type.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	class Airplane : public Model
	{
	public:
		Airplane(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
			AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager,
			const AirplaneType& airplaneType);
		Airplane(const Airplane&);
		Airplane(Airplane&&) noexcept;
		virtual void updateShaders() override;
		void setCtrl(/*const Common::AirplaneCtrl& airplaneCtrl*/);
		virtual ~Airplane() = default;

	private:
		Submodel m_cap;
		Submodel m_propeller;
		Submodel m_body;
		Submodel m_joins;
		Submodel m_tires;
		SpotLight m_leftLight;
		SpotLight m_rightLight;

		virtual void renderSurfaces() const override;
		virtual void renderLights() const override;
	};
};
