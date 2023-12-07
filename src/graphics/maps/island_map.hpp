#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/airport.hpp"
#include "graphics/models/directional_light_model.hpp"
#include "graphics/models/zeppelin.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/world_shading.hpp"

namespace Graphics
{
	class IslandMap : public Map
	{
	public:
		IslandMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
			AssetManager<const Texture>& textureManager);
		void setModels();
		virtual void update(int day, float timeOfDay) override;
		virtual void updateShaders() override;
		virtual void render() const override;
		const DayNightCycle& getDayNightCycle() const;
		virtual ~IslandMap() = default;

	private:
		Airport m_airport;
		Zeppelin m_zeppelin;

		DirectionalLightModel m_moon;
		DirectionalLightModel m_sun;

		DayNightCycle m_dayNightCycle;
	};
};
