#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/models/directional_light_model.hpp"
#include "graphics/models/hills.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/world_shading.hpp"

#include <string>

namespace Graphics
{
	class HillsMap : public Map
	{
	public:
		HillsMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
			const ShaderProgram& lightShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager);
		virtual void update(int day, float timeOfDay) override;
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~HillsMap() = default;

	private:
		Hills m_hills;

		DirectionalLightModel m_moon;
		DirectionalLightModel m_sun;

		DayNightCycle m_dayNightCycle;

		void setModels();
	};
};
