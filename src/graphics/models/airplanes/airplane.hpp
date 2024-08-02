#pragma once

#include "common/airplaneCtrl.hpp"
#include "common/airplaneTypeName.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Airplane : public Model
	{
	public:
		static std::unique_ptr<Airplane> createAirplane(const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<std::string, const Texture>& textureManager,
			Common::AirplaneTypeName airplaneTypeName);
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) = 0;
		virtual int getHP() const;
		virtual void setHP(int hp);
		virtual ~Airplane() = default;

	protected:
		int m_hp{};
	};
};
