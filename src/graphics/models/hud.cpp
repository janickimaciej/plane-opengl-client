#include "graphics/models/hud.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/text_field.hpp"
#include "graphics/texture.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	constexpr float smallFontSize = 0.0003f;
	constexpr float largeFontSize = 0.0006f;
	constexpr float topLineY = 0;
	constexpr float bottomLineLargeFontY = -0.035;
	constexpr float bottomLineSmallFontY = -0.055;
	constexpr float globalY = -0.43;
	constexpr glm::vec3 airspeedPosition{0.78, globalY, 0};
	constexpr glm::vec3 verticalSpeedPosition{0.32, globalY, 0};
	constexpr glm::vec3 hpPosition{-0.06, globalY, 0};
	constexpr glm::vec3 radarAltitudePosition{-0.51, globalY, 0};
	constexpr glm::vec3 altitudePosition{-0.96, globalY, 0};

	HUD::HUD(const ShaderProgram& hudShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		m_hudShaderProgram{hudShaderProgram},
		m_airspeedText{hudShaderProgram, proceduralMeshManager, textureManager, "AIRSPEED",
			airspeedPosition + glm::vec3{0.03, topLineY, 0}, smallFontSize},
		m_airspeedNumber{hudShaderProgram, proceduralMeshManager, textureManager, "____",
			airspeedPosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_airspeedUnit{hudShaderProgram, proceduralMeshManager, textureManager, "KPH",
			airspeedPosition + glm::vec3{0.12, bottomLineSmallFontY, 0}, smallFontSize},
		m_verticalSpeedText{hudShaderProgram, proceduralMeshManager, textureManager,
			"VERTICAL_SPEED", verticalSpeedPosition + glm::vec3{0.01, topLineY, 0}, smallFontSize},
		m_verticalSpeedNumber{hudShaderProgram, proceduralMeshManager, textureManager, "_____",
			verticalSpeedPosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_verticalSpeedUnit{hudShaderProgram, proceduralMeshManager, textureManager, "MPS",
			verticalSpeedPosition + glm::vec3{0.15, bottomLineSmallFontY, 0}, smallFontSize},
		m_hpNumber{hudShaderProgram, proceduralMeshManager, textureManager, "___",
			hpPosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_hpUnit{hudShaderProgram, proceduralMeshManager, textureManager, "HP",
			hpPosition + glm::vec3{0.1, bottomLineSmallFontY, 0}, smallFontSize},
		m_altitudeText{hudShaderProgram, proceduralMeshManager, textureManager, "ALTITUDE",
			altitudePosition + glm::vec3{0.045, topLineY, 0}, smallFontSize},
		m_altitudeNumber{hudShaderProgram, proceduralMeshManager, textureManager, "______",
			altitudePosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_altitudeUnit{hudShaderProgram, proceduralMeshManager, textureManager, "M",
			altitudePosition + glm::vec3{0.17, bottomLineSmallFontY, 0}, smallFontSize},
		m_radarAltitudeText{hudShaderProgram, proceduralMeshManager, textureManager,
			"RADAR_ALTITUDE", radarAltitudePosition + glm::vec3{0.007, topLineY, 0}, smallFontSize},
		m_radarAltitudeNumber{hudShaderProgram, proceduralMeshManager, textureManager, "______",
			radarAltitudePosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_radarAltitudeUnit{hudShaderProgram, proceduralMeshManager, textureManager, "M",
			radarAltitudePosition + glm::vec3{0.17, bottomLineSmallFontY, 0}, smallFontSize}
	{
		for (char i = '0'; i <= '9'; ++i)
		{
			m_textureLocks.push_back(textureManager.get(texturePath("characters", std::string{i})));
		}
	}

	void HUD::updateShaders()
	{ }

	void HUD::render() const
	{
		m_hudShaderProgram.use();
		renderHUD();
	}

	void HUD::update(const Airplane& ownAirplane, const Map& map)
	{
		m_lastUpdateTime += Time::getDeltaTime();
		constexpr float refreshTime = 0.5f;
		if (m_lastUpdateTime >= refreshTime)
		{
			Common::State state = ownAirplane.getState();
			refresh(m_airspeedNumber, static_cast<int>(3.6f * glm::length(state.velocity)), 4,
				false);
			refresh(m_verticalSpeedNumber, static_cast<int>((state.orientation * state.velocity).y),
				4, true);
			refresh(m_altitudeNumber, static_cast<int>(state.position.y), 5, true);
			refresh(m_radarAltitudeNumber, static_cast<int>(state.position.y -
				map.getHeight(state.position.x, state.position.z)), 5, true);
			refresh(m_hpNumber, ownAirplane.getHP(), 3, false);
			m_lastUpdateTime = 0;
		}
	}

	void HUD::renderHUD() const
	{
		m_airspeedText.render(getMatrix());
		m_airspeedNumber.render(getMatrix());
		m_airspeedUnit.render(getMatrix());
		m_verticalSpeedText.render(getMatrix());
		m_verticalSpeedNumber.render(getMatrix());
		m_verticalSpeedUnit.render(getMatrix());
		m_altitudeText.render(getMatrix());
		m_altitudeNumber.render(getMatrix());
		m_altitudeUnit.render(getMatrix());
		m_radarAltitudeText.render(getMatrix());
		m_radarAltitudeNumber.render(getMatrix());
		m_radarAltitudeUnit.render(getMatrix());
		m_hpNumber.render(getMatrix());
		m_hpUnit.render(getMatrix());
	}

	void HUD::refresh(TextField& textField, int value, int numberOfDigits, bool isSigned)
	{
		if (isSigned)
		{
			if (value < 0)
			{
				value = -value;
				textField.setCharacter(0, '-');
			}
			else
			{
				textField.setCharacter(0, '_');
			}
		}
		float eps = 0.001f;
		std::string text =
			std::to_string(value % static_cast<int>(std::pow(10, numberOfDigits) + eps));
		std::size_t offset = numberOfDigits - text.size();
		for (std::size_t i = 0; i < offset; ++i)
		{
			textField.setCharacter(isSigned ? i + 1 : i, '_');
		}
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			textField.setCharacter(isSigned ? i + 1 + offset : i + offset, text[i]);
		}
	}
};
