#pragma once

#include "common/terrains/maps/map.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/dayNightCycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airport.hpp"
#include "graphics/models/directionalLightModel.hpp"
#include "graphics/models/zeppelin.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class AirportMap : public Map
	{
	public:
		AirportMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram,
			AssetManager<std::string, const Mesh>& fileMeshManager,
			AssetManager<std::string, const Texture>& textureManager,
			std::unique_ptr<Common::Terrains::Map> terrain);
		virtual void update(int day, float timeOfDay) override;
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~AirportMap() = default;

	private:
		Airport m_airport;
		Zeppelin m_zeppelin;

		DirectionalLightModel m_moon;
		DirectionalLightModel m_sun;

		DayNightCycle m_dayNightCycle;

		void setModels();
	};
};
