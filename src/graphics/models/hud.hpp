#pragma once

#include "graphics/asset_manager.hpp"
#include "graphics/models/model.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/text_field.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <string>

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
		void update(int airspeed, int altitude, int hp);

	private:
		const ShaderProgram& m_hudShaderProgram;

		TextField m_airspeedText;
		TextField m_airspeedNumber;
		TextField m_airspeedUnit;
		TextField m_altitudeText;
		TextField m_altitudeNumber;
		TextField m_altitudeUnit;
		TextField m_hpNumber;
		TextField m_hpUnit;

		void renderHUD() const;
		void updateAirspeed(int airspeed);
		void updateAltitude(int altitude);
		void updateHP(int hp);
	};
};
