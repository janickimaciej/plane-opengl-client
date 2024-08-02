#include "graphics/models/airplanes/mustang.hpp"

#include "common/airplaneCentersOfMass.hpp"
#include "common/airplaneCtrl.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/texture.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	static const std::string modelName = "mustang";
	
	static const std::string capPath = meshPath(modelName, "cap");
	static const std::string propellerPath = meshPath(modelName, "propeller");
	static const std::string fuselagePath = meshPath(modelName, "body");
	static const std::string joinsPath = meshPath(modelName, "joins");
	static const std::string tiresPath = meshPath(modelName, "tires");
	static const std::string lightPath = meshPath(modelName, "light");

	static const std::string camoPath = texturePath(modelName, "camo");

	static constexpr float lightsAttenuationQuadratic = 0.0001f;
	static constexpr float lightsAttenuationLinear = 0.0005f;
	static constexpr float lightsAttenuationConstant = 1;
	static constexpr glm::vec3 lightsColor{1, 1, 1};
	static constexpr float lightsCutoffInnerDeg = 8;
	static constexpr float lightsCutoffOuterDeg = 10;

	static const Material texturedMetal{glm::vec3{1, 1, 1}, 0.75f, 0.5f, 30, true};
	static const Material metal{glm::vec3{0.25f, 0.25f, 0.25f}, 0.75f, 0.5f, 30, true};
	static const Material rubber{glm::vec3{0.1f, 0.1f, 0.1f}, 0.75f, 0, 1, false};
	static const Material whiteLightGlass{glm::vec3{1, 1, 1}, 1, 1, 1, false};

	Mustang::Mustang(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		m_surfaceShaderProgram{surfaceShaderProgram},
		m_lightShaderProgram{lightShaderProgram},
		m_cap{surfaceShaderProgram, fileMeshManager.get(capPath), metal},
		m_propeller{surfaceShaderProgram, fileMeshManager.get(propellerPath), metal},
		m_body{surfaceShaderProgram, fileMeshManager.get(fuselagePath), texturedMetal,
			textureManager.get(camoPath)},
		m_joins{surfaceShaderProgram, fileMeshManager.get(joinsPath), metal},
		m_tires{surfaceShaderProgram, fileMeshManager.get(tiresPath), rubber},
		m_leftLight{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, glm::radians(lightsCutoffInnerDeg),
			glm::radians(lightsCutoffOuterDeg)},
		m_leftLightSubmodel{m_leftLight, lightShaderProgram, fileMeshManager.get(lightPath),
			whiteLightGlass},
		m_rightLight{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, glm::radians(lightsCutoffInnerDeg),
			glm::radians(lightsCutoffOuterDeg)},
		m_rightLightSubmodel{m_rightLight, lightShaderProgram, fileMeshManager.get(lightPath),
			whiteLightGlass}
	{
		static constexpr float lightsPositionXAbs = 2.14f;
		static constexpr float lightsPositionY = -0.474f;
		static constexpr float lightsPositionZ = 2.938f;
		m_leftLight.translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ});
		m_rightLight.translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ});

		static constexpr glm::vec3 nosePosition = -Common::airplaneCentersOfMass[
			toSizeT(Common::AirplaneTypeName::mustang)];
		m_cap.translate(nosePosition);
		m_propeller.translate(nosePosition);
		m_body.translate(nosePosition);
		m_joins.translate(nosePosition);
		m_tires.translate(nosePosition);
		m_leftLight.translate(nosePosition);
		m_rightLight.translate(nosePosition);
	}

	void Mustang::updateShaders()
	{
		m_leftLight.updateShaders(getMatrix());
		m_rightLight.updateShaders(getMatrix());
	}

	void Mustang::render() const
	{
		m_surfaceShaderProgram.use();
		renderSurfaces();

		m_lightShaderProgram.use();
		renderLights();
	}

	void Mustang::setCtrl(const Common::AirplaneCtrl& airplaneCtrl)
	{
		static constexpr float maxPropellerAngVelocityDeg = 2 * 360;
		m_propellerAngVelocityDeg = airplaneCtrl.thrustRelative * maxPropellerAngVelocityDeg;
		m_propeller.rotateRoll(glm::radians(m_propellerAngVelocityDeg) * Time::getDeltaTime());
	}

	void Mustang::setHP(int hp)
	{
		static const Material red{glm::vec3{1, 0, 0}, 1, 0, 1, false};
		if (!m_isDestroyed && hp == 0)
		{
			m_cap.setMaterial(red);
			m_propeller.setMaterial(red);
			m_body.setMaterial(red);
			m_joins.setMaterial(red);
			m_tires.setMaterial(red);
			m_leftLightSubmodel.setMaterial(red);
			m_rightLightSubmodel.setMaterial(red);
			m_isDestroyed = true;
		}
		else if (m_isDestroyed && hp > 0)
		{
			m_cap.setMaterial(metal);
			m_propeller.setMaterial(metal);
			m_body.setMaterial(texturedMetal);
			m_joins.setMaterial(metal);
			m_tires.setMaterial(rubber);
			m_leftLightSubmodel.setMaterial(whiteLightGlass);
			m_rightLightSubmodel.setMaterial(whiteLightGlass);
			m_isDestroyed = false;
		}
		Airplane::setHP(hp);
	}
	
	void Mustang::renderSurfaces() const
	{
		m_cap.render(getMatrix());
		m_propeller.render(getMatrix());
		m_body.render(getMatrix());
		m_joins.render(getMatrix());
		m_tires.render(getMatrix());
	}

	void Mustang::renderLights() const
	{
		m_leftLightSubmodel.render(getMatrix());
		m_rightLightSubmodel.render(getMatrix());
	}
};
