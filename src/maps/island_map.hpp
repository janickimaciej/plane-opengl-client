#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/world_shading.hpp"
#include "maps/map.hpp"
#include "models/directional_light_model.hpp"
#include "models/zeppelin.hpp"

class IslandMap : public Map
{
public:
	IslandMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager);
	void setModels();
	virtual void update(const Map& previousMap) override;
	virtual void render() const override;
	const DayNightCycle& getDayNightCycle() const;

private:
	Zeppelin m_zeppelin;

	DirectionalLightModel m_moon;
	DirectionalLightModel m_sun;

	DayNightCycle m_dayNightCycle;
};
