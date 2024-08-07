#include "graphics/models/hud.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/textField.hpp"
#include "graphics/texture.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	static constexpr float smallFontSize = 0.0003f;
	static constexpr float largeFontSize = 0.0006f;
	static constexpr float topLineY = 0;
	static constexpr float bottomLineLargeFontY = -0.035f;
	static constexpr float bottomLineSmallFontY = -0.055f;
	static constexpr float indicatorsY = -0.43f;
	static constexpr glm::vec3 fpsPosition{-0.97f, 0.53f, 0};
	static constexpr glm::vec3 playerCountPosition{0.84f, 0.53f, 0};
	static constexpr glm::vec3 altitudePosition{-0.96f, indicatorsY, 0};
	static constexpr glm::vec3 radarAltitudePosition{-0.51f, indicatorsY, 0};
	static constexpr glm::vec3 hpPosition{-0.06f, indicatorsY, 0};
	static constexpr glm::vec3 verticalSpeedPosition{0.32f, indicatorsY, 0};
	static constexpr glm::vec3 airspeedPosition{0.78f, indicatorsY, 0};

	HUD::HUD(const ShaderProgram& hudShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		m_hudShaderProgram{hudShaderProgram},
		m_fpsNumber{hudShaderProgram, proceduralMeshManager, textureManager, "___",
			fpsPosition + glm::vec3{0, 0, 0}, smallFontSize},
		m_fpsUnit{hudShaderProgram, proceduralMeshManager, textureManager, "FPS",
			fpsPosition + glm::vec3{0.05f, 0, 0}, smallFontSize},
		m_playerCountNumber{hudShaderProgram, proceduralMeshManager, textureManager, "__",
			playerCountPosition + glm::vec3{0, 0, 0}, smallFontSize},
		m_playerCountUnit{hudShaderProgram, proceduralMeshManager, textureManager, "PLAYERS",
			playerCountPosition + glm::vec3{0.04f, 0, 0}, smallFontSize},
		m_altitudeText{hudShaderProgram, proceduralMeshManager, textureManager, "ALTITUDE",
			altitudePosition + glm::vec3{0.045f, topLineY, 0}, smallFontSize},
		m_altitudeNumber{hudShaderProgram, proceduralMeshManager, textureManager, "______",
			altitudePosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_altitudeUnit{hudShaderProgram, proceduralMeshManager, textureManager, "M",
			altitudePosition + glm::vec3{0.17f, bottomLineSmallFontY, 0}, smallFontSize},
		m_radarAltitudeText{hudShaderProgram, proceduralMeshManager, textureManager,
			"RADAR_ALTITUDE", radarAltitudePosition + glm::vec3{0.007f, topLineY, 0},
			smallFontSize},
		m_radarAltitudeNumber{hudShaderProgram, proceduralMeshManager, textureManager, "______",
			radarAltitudePosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_radarAltitudeUnit{hudShaderProgram, proceduralMeshManager, textureManager, "M",
			radarAltitudePosition + glm::vec3{0.17f, bottomLineSmallFontY, 0}, smallFontSize},
		m_hpNumber{hudShaderProgram, proceduralMeshManager, textureManager, "___",
			hpPosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_hpUnit{hudShaderProgram, proceduralMeshManager, textureManager, "HP",
			hpPosition + glm::vec3{0.1f, bottomLineSmallFontY, 0}, smallFontSize},
		m_verticalSpeedText{hudShaderProgram, proceduralMeshManager, textureManager,
			"VERTICAL_SPEED", verticalSpeedPosition + glm::vec3{0.01f, topLineY, 0}, smallFontSize},
		m_verticalSpeedNumber{hudShaderProgram, proceduralMeshManager, textureManager, "_____",
			verticalSpeedPosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_verticalSpeedUnit{hudShaderProgram, proceduralMeshManager, textureManager, "MPS",
			verticalSpeedPosition + glm::vec3{0.15f, bottomLineSmallFontY, 0}, smallFontSize},
		m_airspeedText{hudShaderProgram, proceduralMeshManager, textureManager, "AIRSPEED",
			airspeedPosition + glm::vec3{0.03f, topLineY, 0}, smallFontSize},
		m_airspeedNumber{hudShaderProgram, proceduralMeshManager, textureManager, "____",
			airspeedPosition + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize},
		m_airspeedUnit{hudShaderProgram, proceduralMeshManager, textureManager, "KPH",
			airspeedPosition + glm::vec3{0.12f, bottomLineSmallFontY, 0}, smallFontSize}
	{
		for (char i = '0'; i <= '9'; ++i)
		{
			m_textureLocks.push_back(textureManager.get(texturePath("characters", std::string{i})));
		}
		m_textureLocks.push_back(textureManager.get(texturePath("characters", "-")));
	}

	void HUD::updateShaders()
	{ }

	void HUD::render() const
	{
		m_hudShaderProgram.use();
		renderHUD();
	}

	void HUD::update(const Airplane& ownAirplane, const Map& map, int playerCount)
	{
		m_lastUpdateTime += Time::getDeltaTime();
		static constexpr float refreshTime = 0.5f;
		if (m_lastUpdateTime >= refreshTime)
		{
			Common::State state = ownAirplane.getState();
			int fps = Time::getFPS();
			refresh(m_fpsNumber, fps, 3, false);
			refresh(m_playerCountNumber, playerCount, 2, false);
			m_playerCountUnit.setCharacter(6, playerCount == 1 ? '_' : 'S');
			refresh(m_altitudeNumber, static_cast<int>(state.position.y), 5, true);
			refresh(m_radarAltitudeNumber, static_cast<int>(state.position.y -
				map.getHeight(state.position.x, state.position.z)), 5, true);
			refresh(m_hpNumber, ownAirplane.getHP(), 3, false);
			refresh(m_verticalSpeedNumber, static_cast<int>((state.orientation * state.velocity).y),
				4, true);
			refresh(m_airspeedNumber, static_cast<int>(3.6f * glm::length(state.velocity)), 4,
				false);
			m_lastUpdateTime = 0;
		}
	}

	void HUD::renderHUD() const
	{
		glm::mat4 modelMatrix = getMatrix();

		m_fpsNumber.render(modelMatrix);
		m_fpsUnit.render(modelMatrix);

		m_playerCountNumber.render(modelMatrix);
		m_playerCountUnit.render(modelMatrix);

		m_altitudeText.render(modelMatrix);
		m_altitudeNumber.render(modelMatrix);
		m_altitudeUnit.render(modelMatrix);

		m_radarAltitudeText.render(modelMatrix);
		m_radarAltitudeNumber.render(modelMatrix);
		m_radarAltitudeUnit.render(modelMatrix);

		m_hpNumber.render(modelMatrix);
		m_hpUnit.render(modelMatrix);

		m_verticalSpeedText.render(modelMatrix);
		m_verticalSpeedNumber.render(modelMatrix);
		m_verticalSpeedUnit.render(modelMatrix);

		m_airspeedText.render(modelMatrix);
		m_airspeedNumber.render(modelMatrix);
		m_airspeedUnit.render(modelMatrix);
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
		static constexpr float eps = 0.001f;
		int upperBound = static_cast<int>(std::pow(10, numberOfDigits) + eps);
		std::string text = std::to_string(value >= upperBound ? upperBound - 1 : value);
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
