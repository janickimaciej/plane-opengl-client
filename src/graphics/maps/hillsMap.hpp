#pragma once

#include "common/terrains/maps/map.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/dayNightCycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/models/directionalLightModel.hpp"
#include "graphics/models/hills.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class HillsMap : public Map
	{
	public:
		HillsMap(WorldShading& worldShading, const ShaderProgram& surfaceShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager,
			std::unique_ptr<Common::Terrains::Map> terrain);
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
