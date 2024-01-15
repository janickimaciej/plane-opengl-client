#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/models/model.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/text_field.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Graphics
{
	class HUD : public Model
	{
	public:
		HUD(const ShaderProgram& hudShaderProgram,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager, const glm::vec3& offset);
		virtual void updateShaders() override;
		virtual void render() const override;
		void update(const Airplane& ownAirplane, const Map& map);

	private:
		const ShaderProgram& m_hudShaderProgram;

		TextField m_airspeedText;
		TextField m_airspeedNumber;
		TextField m_airspeedUnit;
		TextField m_verticalSpeedText;
		TextField m_verticalSpeedNumber;
		TextField m_verticalSpeedUnit;
		TextField m_altitudeText;
		TextField m_altitudeNumber;
		TextField m_altitudeUnit;
		TextField m_radarAltitudeText;
		TextField m_radarAltitudeNumber;
		TextField m_radarAltitudeUnit;
		TextField m_hpNumber;
		TextField m_hpUnit;

		std::vector<std::shared_ptr<const Texture>> m_textureLocks{};

		float m_lastUpdateTime = 1;

		void renderHUD() const;
		void refresh(TextField& textField, int value, int numberOfDigits, bool isSigned);
	};
};
