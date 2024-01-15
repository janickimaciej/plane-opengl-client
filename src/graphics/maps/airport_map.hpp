#pragma once

#include "common/terrains/maps/map.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airport.hpp"
#include "graphics/models/directional_light_model.hpp"
#include "graphics/models/zeppelin.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/world_shading.hpp"

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
