#include "graphics/models/airplane.hpp"

#include "common/airplane_ctrl.hpp"
#include "graphics/airplane_type.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
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

	Airplane::Airplane(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
		AssetManager<const Texture>& textureManager, const AirplaneType& airplaneType) :
		Model{surfaceShaderProgram, lightShaderProgram},
		m_cap{surfaceShaderProgram, meshManager.get(airplaneType.cap), metal},
		m_propeller{surfaceShaderProgram, meshManager.get(airplaneType.propeller), metal},
		m_body{surfaceShaderProgram, meshManager.get(airplaneType.body), defaultMaterial,
			textureManager.get(airplaneType.camo)},
		m_joins{surfaceShaderProgram, meshManager.get(airplaneType.joins), metal},
		m_tires{surfaceShaderProgram, meshManager.get(airplaneType.tires), rubber},
		m_leftLight{surfaceShaderProgram, lightsAttenuationQuadratic, lightsAttenuationLinear,
			lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg,
			Submodel{lightShaderProgram, meshManager.get(airplaneType.light), whiteLightGlass}},
		m_rightLight{surfaceShaderProgram, lightsAttenuationQuadratic, lightsAttenuationLinear,
			lightsAttenuationConstant, lightsColor, lightsCutoffInnerDeg, lightsCutoffOuterDeg,
			Submodel{lightShaderProgram, meshManager.get(airplaneType.light), whiteLightGlass}}
	{
		constexpr float lightsPositionXAbs = 2.14f;
		constexpr float lightsPositionY = -0.474f;
		constexpr float lightsPositionZ = 2.938f;
		m_leftLight.translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ});
		m_rightLight.translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ});

		m_cap.translate(airplaneType.nosePosition);
		m_propeller.translate(airplaneType.nosePosition);
		m_body.translate(airplaneType.nosePosition);
		m_joins.translate(airplaneType.nosePosition);
		m_tires.translate(airplaneType.nosePosition);
		m_leftLight.translate(airplaneType.nosePosition);
		m_rightLight.translate(airplaneType.nosePosition);
	}

	Airplane::Airplane(const Airplane& airplane) :
		Model{airplane.m_surfaceShaderProgram, airplane.m_lightShaderProgram},
		m_cap{airplane.m_cap},
		m_propeller{airplane.m_propeller},
		m_body{airplane.m_body},
		m_joins{airplane.m_joins},
		m_tires{airplane.m_tires},
		m_leftLight{airplane.m_leftLight},
		m_rightLight{airplane.m_rightLight}
	{ }

	Airplane::Airplane(Airplane&& airplane) noexcept :
		Model{airplane.m_surfaceShaderProgram, airplane.m_lightShaderProgram},
		m_cap{airplane.m_cap},
		m_propeller{airplane.m_propeller},
		m_body{airplane.m_body},
		m_joins{airplane.m_joins},
		m_tires{airplane.m_tires},
		m_leftLight{airplane.m_leftLight},
		m_rightLight{airplane.m_rightLight}
	{ }

	void Airplane::updateShaders()
	{
		m_leftLight.updateShaders(getMatrix());
		m_rightLight.updateShaders(getMatrix());
	}

	void Airplane::setCtrl(/*const Common::AirplaneCtrl& airplaneCtrl*/)
	{
		/*m_elevator.resetRotation(); //tmpc
		m_elevator.pitch(-m_airplaneCtrl.elevatorAngleRad);
		m_rudder.resetRotation();
		m_rudder.yaw(m_airplaneCtrl.rudderAngleRad);
		m_leftAileron.resetRotation();
		m_leftAileron.pitch(m_airplaneCtrl.aileronsAngleRad);
		m_rightAileron.resetRotation();
		m_rightAileron.pitch(-m_airplaneCtrl.aileronsAngleRad);*/ //tmpc
	}

	void Airplane::renderSurfaces() const
	{
		m_cap.render(getMatrix());
		m_propeller.render(getMatrix());
		m_body.render(getMatrix());
		m_joins.render(getMatrix());
		m_tires.render(getMatrix());
	}

	void Airplane::renderLights() const
	{
		m_leftLight.render(getMatrix());
		m_rightLight.render(getMatrix());
	}
};
