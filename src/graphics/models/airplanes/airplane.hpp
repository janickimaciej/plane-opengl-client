#pragma once

#include "common/airplane_ctrl.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <memory>

namespace Graphics
{
	class Airplane : public Model
	{
	public:
		static std::unique_ptr<Airplane> createAirplane(const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
			AssetManager<const Texture>& textureManager, Common::AirplaneTypeName airplaneTypeName);
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) = 0;
		virtual ~Airplane() = default;

	protected:
		Airplane(const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram);
	};
};
