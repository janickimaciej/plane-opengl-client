#include "graphics/models/hud.hpp"

#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/procedural_mesh_name.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/text_field.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>

namespace Graphics
{
	HUD::HUD(const ShaderProgram& hudShaderProgram,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager, const glm::vec3& offset) :
		m_hudShaderProgram{hudShaderProgram},
		m_airspeedText{hudShaderProgram, proceduralMeshManager, textureManager, "AIRSPEED",
			offset + glm::vec3{3.5, -2.9, 0}, 0.005f},
		m_airspeedNumber{hudShaderProgram, proceduralMeshManager, textureManager, "____",
			offset + glm::vec3{3.4, -3.4, 0}, 0.007f},
		m_airspeedUnit{hudShaderProgram, proceduralMeshManager, textureManager, "KPH",
			offset + glm::vec3{4.7, -3.52, 0}, 0.005f},
		m_altitudeText{hudShaderProgram, proceduralMeshManager, textureManager, "ALTITUDE",
			offset + glm::vec3{-5.2, -2.9, 0}, 0.005f},
		m_altitudeNumber{hudShaderProgram, proceduralMeshManager, textureManager, "______",
			offset + glm::vec3{-5.35, -3.4, 0}, 0.007f},
		m_altitudeUnit{hudShaderProgram, proceduralMeshManager, textureManager, "M",
			offset + glm::vec3{-3.5, -3.52, 0}, 0.005f},
		m_hpNumber{hudShaderProgram, proceduralMeshManager, textureManager, "___",
			offset + glm::vec3{-0.5, -3.4, 0}, 0.007f},
		m_hpUnit{hudShaderProgram, proceduralMeshManager, textureManager, "HP",
			offset + glm::vec3{0.5, -3.52, 0}, 0.005f}
	{ }

	void HUD::updateShaders()
	{ }

	void HUD::render() const
	{
		m_hudShaderProgram.use();
		renderHUD();
	}

	void HUD::update(int airspeed, int altitude, int hp)
	{
		updateAirspeed(airspeed);
		updateAltitude(altitude);
		updateHP(hp);
	}

	void HUD::renderHUD() const
	{
		m_airspeedText.render(getMatrix());
		m_airspeedNumber.render(getMatrix());
		m_airspeedUnit.render(getMatrix());
		m_altitudeText.render(getMatrix());
		m_altitudeNumber.render(getMatrix());
		m_altitudeUnit.render(getMatrix());
		m_hpNumber.render(getMatrix());
		m_hpUnit.render(getMatrix());
	}

	void HUD::updateAirspeed(int airspeed)
	{
		std::string text = std::to_string(airspeed % 10000);
		constexpr std::size_t numberOfDigits = 4;
		std::size_t offset = numberOfDigits - text.size();
		std::array<char, numberOfDigits> digits{};
		for (std::size_t i = 0; i < numberOfDigits; ++i)
		{
			digits[i] = '_';
		}
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			digits[i + offset] = text[i];
		}
		for (std::size_t i = 0; i < numberOfDigits; ++i)
		{
			m_airspeedNumber.setCharacter(i, digits[i]);
		}
	}

	void HUD::updateAltitude(int altitude)
	{
		if (altitude < 0)
		{
			altitude = -altitude;
			m_altitudeNumber.setCharacter(0, '-');
		}
		else
		{
			m_altitudeNumber.setCharacter(0, '_');
		}
		std::string text = std::to_string(altitude % 100000);
		constexpr std::size_t numberOfDigits = 5;
		std::size_t offset = numberOfDigits - text.size();
		std::array<char, numberOfDigits> digits{};
		for (std::size_t i = 1; i < numberOfDigits; ++i)
		{
			digits[i] = '_';
		}
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			digits[i + offset] = text[i];
		}
		for (std::size_t i = 1; i < numberOfDigits; ++i)
		{
			m_altitudeNumber.setCharacter(i + 1, digits[i]);
		}
	}

	void HUD::updateHP(int hp)
	{
		std::string text = std::to_string(hp);
		constexpr std::size_t numberOfDigits = 3;
		std::size_t offset = numberOfDigits - text.size();
		std::array<char, numberOfDigits> digits{};
		for (std::size_t i = 0; i < numberOfDigits; ++i)
		{
			digits[i] = '_';
		}
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			digits[i + offset] = text[i];
		}
		for (std::size_t i = 0; i < numberOfDigits; ++i)
		{
			m_hpNumber.setCharacter(i, digits[i]);
		}
	}
};
