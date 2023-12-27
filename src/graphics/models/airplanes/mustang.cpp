#include "graphics/models/airplanes/mustang.hpp"

#include "common/airplane_center_of_mass_database.hpp"
#include "common/airplane_ctrl.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	const std::string modelName = "mustang";
	
	const std::string capPath = meshPath(modelName, "cap");
	const std::string propellerPath = meshPath(modelName, "propeller");
	const std::string fuselagePath = meshPath(modelName, "body");
	const std::string joinsPath = meshPath(modelName, "joins");
	const std::string tiresPath = meshPath(modelName, "tires");
	const std::string lightPath = meshPath(modelName, "light");

	const std::string camoPath = texturePath(modelName, "camo");

	constexpr float lightsAttenuationQuadratic = 0.0001f;
	constexpr float lightsAttenuationLinear = 0.0005f;
	constexpr float lightsAttenuationConstant = 1;
	constexpr glm::vec3 lightsColor{1, 1, 1};
	constexpr float lightsCutoffInnerDeg = 8;
	constexpr float lightsCutoffOuterDeg = 10;

	// dummy color
	const Material defaultMaterial{glm::vec3{1, 0, 0}, 0.75, 0.25, 10};
	const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.25, 10};
	const Material rubber{glm::vec3{0.1, 0.1, 0.1}, 0.75, 0.25, 10};
	// dummy surface params
	const Material whiteLightGlass{glm::vec3{1, 1, 1}, 1, 1, 1};

	Mustang::Mustang(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
		AssetManager<const Texture>& textureManager) :
		Airplane{surfaceShaderProgram, lightShaderProgram},
		m_cap{surfaceShaderProgram, meshManager.get(capPath), metal},
		m_propeller{surfaceShaderProgram, meshManager.get(propellerPath), metal},
		m_fuselage{surfaceShaderProgram, meshManager.get(fuselagePath), defaultMaterial,
			textureManager.get(camoPath)},
		m_joins{surfaceShaderProgram, meshManager.get(joinsPath), metal},
		m_tires{surfaceShaderProgram, meshManager.get(tiresPath), rubber},
		m_leftLight{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, glm::radians(lightsCutoffInnerDeg),
			glm::radians(lightsCutoffOuterDeg)},
		m_leftLightSubmodel{m_leftLight, lightShaderProgram, meshManager.get(lightPath),
			whiteLightGlass},
		m_rightLight{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, glm::radians(lightsCutoffInnerDeg),
			glm::radians(lightsCutoffOuterDeg)},
		m_rightLightSubmodel{m_rightLight, lightShaderProgram, meshManager.get(lightPath),
			whiteLightGlass}
	{
		constexpr float lightsPositionXAbs = 2.14f;
		constexpr float lightsPositionY = -0.474f;
		constexpr float lightsPositionZ = 2.938f;
		m_leftLight.translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ});
		m_rightLight.translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ});

		constexpr glm::vec3 nosePosition = -Common::airplaneCenterOfMassDatabase[
			static_cast<std::size_t>(Common::AirplaneTypeName::mustang)];
		m_cap.translate(nosePosition);
		m_propeller.translate(nosePosition);
		m_fuselage.translate(nosePosition);
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

	void Mustang::setCtrl(const Common::AirplaneCtrl& airplaneCtrl)
	{
		static constexpr float maxPropellerAngVelocityDeg = 2 * 360;
		m_propellerAngVelocityDeg = airplaneCtrl.thrustRelative * maxPropellerAngVelocityDeg;
		m_propeller.rotateRoll(glm::radians(m_propellerAngVelocityDeg) * Time::getDeltaTime());
	}
	
	void Mustang::renderSurfaces() const
	{
		m_cap.render(getMatrix());
		m_propeller.render(getMatrix());
		m_fuselage.render(getMatrix());
		m_joins.render(getMatrix());
		m_tires.render(getMatrix());
	}

	void Mustang::renderLights() const
	{
		m_leftLightSubmodel.render(getMatrix());
		m_rightLightSubmodel.render(getMatrix());
	}
};
