#include "graphics/models/airplanes/jw1.hpp"

#include "common/airplane_center_of_mass_database.hpp"
#include "common/airplane_ctrl.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

#include <string>

namespace Graphics
{
	const std::string modelName = "jw1";
	
	const std::string conePath = meshPath(modelName, "cone");
	const std::string gunPath = meshPath(modelName, "gun");
	const std::string cockpitPath = meshPath(modelName, "cockpit");
	const std::string fuselagePath = meshPath(modelName, "fuselage");
	const std::string rightEnginePath = meshPath(modelName, "rightEngine");
	const std::string rightNozzlePath = meshPath(modelName, "rightNozzle");
	const std::string rightWingPath = meshPath(modelName, "rightWing");
	const std::string rightVStabPath = meshPath(modelName, "rightVStab");
	const std::string rightElevatorPath = meshPath(modelName, "rightElevator");
	const std::string rightRudderPath = meshPath(modelName, "rightRudder");
	const std::string rightAileronPath = meshPath(modelName, "rightAileron");

	constexpr float lightsAttenuationQuadratic = 0.0001f;
	constexpr float lightsAttenuationLinear = 0.0005f;
	constexpr float lightsAttenuationConstant = 1;
	constexpr glm::vec3 lightsColor{1, 1, 1};
	
	// dummy color
	const Material defaultMaterial{glm::vec3{1, 0, 0}, 0.75, 0.25, 10};
	const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.25, 10};
	const Material blackGlass{glm::vec3{0, 0, 0}, 0.75, 0.9, 10};
	
	JW1::JW1(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<const Mesh>& meshManager, AssetManager<const Texture>& textureManager) :
		Airplane{surfaceShaderProgram, lightShaderProgram},
		m_cone{surfaceShaderProgram, meshManager.get(conePath), metal},
		m_gun{surfaceShaderProgram, meshManager.get(gunPath), metal},
		m_cockpit{surfaceShaderProgram, meshManager.get(cockpitPath), blackGlass},
		m_fuselage{surfaceShaderProgram, meshManager.get(fuselagePath), metal},
		m_leftEngine{surfaceShaderProgram, meshManager.get(rightEnginePath), metal},
		m_rightEngine{surfaceShaderProgram, meshManager.get(rightEnginePath), metal},
		m_leftNozzle{surfaceShaderProgram, meshManager.get(rightNozzlePath), metal},
		m_rightNozzle{surfaceShaderProgram, meshManager.get(rightNozzlePath), metal},
		m_leftWing{surfaceShaderProgram, meshManager.get(rightWingPath), metal},
		m_rightWing{surfaceShaderProgram, meshManager.get(rightWingPath), metal},
		m_leftVStab{surfaceShaderProgram, meshManager.get(rightVStabPath), metal},
		m_rightVStab{surfaceShaderProgram, meshManager.get(rightVStabPath), metal},
		m_leftElevator{surfaceShaderProgram, meshManager.get(rightElevatorPath), metal},
		m_rightElevator{surfaceShaderProgram, meshManager.get(rightElevatorPath), metal},
		m_leftRudder{surfaceShaderProgram, meshManager.get(rightRudderPath), metal},
		m_rightRudder{surfaceShaderProgram, meshManager.get(rightRudderPath), metal},
		m_leftAileron{surfaceShaderProgram, meshManager.get(rightAileronPath), metal},
		m_rightAileron{surfaceShaderProgram, meshManager.get(rightAileronPath), metal},
		m_leftNozzleLight{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant},
		m_rightNozzleLight{surfaceShaderProgram, lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant}
	{
		m_leftEngine.mirrorX();
		m_leftNozzle.mirrorX();
		m_leftWing.mirrorX();
		m_leftVStab.mirrorX();
		m_leftElevator.mirrorX();
		m_leftRudder.mirrorX();
		m_leftAileron.mirrorX();

		m_leftElevator.translate(glm::vec3{0, 0, 16.6});
		m_rightElevator.translate(glm::vec3{0, 0, 16.6});
		m_leftRudder.translate(glm::vec3{-1.375, 0.533, 18.98});
		m_rightRudder.translate(glm::vec3{1.375, 0.533, 18.98});
		m_leftAileron.translate(glm::vec3{-4.107, 0.535, 14.57});
		m_rightAileron.translate(glm::vec3{4.107, 0.535, 14.57});

		constexpr glm::vec3 nosePosition = -Common::airplaneCenterOfMassDatabase[
			static_cast<std::size_t>(Common::AirplaneTypeName::jw1)];
		m_cone.translate(nosePosition);
		m_gun.translate(nosePosition);
		m_cockpit.translate(nosePosition);
		m_fuselage.translate(nosePosition);
		m_leftEngine.translate(nosePosition);
		m_rightEngine.translate(nosePosition);
		m_leftNozzle.translate(nosePosition);
		m_rightNozzle.translate(nosePosition);
		m_leftWing.translate(nosePosition);
		m_rightWing.translate(nosePosition);
		m_leftVStab.translate(nosePosition);
		m_rightVStab.translate(nosePosition);
		m_leftElevator.translate(nosePosition);
		m_rightElevator.translate(nosePosition);
		m_leftRudder.translate(nosePosition);
		m_rightRudder.translate(nosePosition);
		m_leftAileron.translate(nosePosition);
		m_rightAileron.translate(nosePosition);
	}

	void JW1::updateShaders()
	{
		m_leftNozzleLight.updateShaders(getMatrix());
		m_rightNozzleLight.updateShaders(getMatrix());
	}

	void JW1::setCtrl(const Common::AirplaneCtrl& airplaneCtrl)
	{
		m_leftElevator.resetRotation();
		m_leftElevator.rotatePitch(-airplaneCtrl.elevatorAngleRad);
		m_rightElevator.resetRotation();
		m_rightElevator.rotatePitch(-airplaneCtrl.elevatorAngleRad);

		static const glm::vec3 rudderAxis = glm::normalize(glm::vec3{0, 654, 261});
		m_leftRudder.resetRotation();
		m_leftRudder.rotate(rudderAxis, airplaneCtrl.rudderAngleRad);
		m_rightRudder.resetRotation();
		m_rightRudder.rotate(rudderAxis, airplaneCtrl.rudderAngleRad);

		static const glm::vec3 rightElevatorAxis = glm::normalize(glm::vec3{888, -45, 297});
		static const glm::vec3 leftElevatorAxis = glm::normalize(glm::vec3{-888, -45, 297});
		m_leftAileron.resetRotation();
		m_leftAileron.rotate(leftElevatorAxis, -airplaneCtrl.aileronsAngleRad);
		m_rightAileron.resetRotation();
		m_rightAileron.rotate(rightElevatorAxis, -airplaneCtrl.aileronsAngleRad);
	}

	void JW1::renderSurfaces() const
	{
		m_cone.render(getMatrix());
		m_gun.render(getMatrix());
		m_cockpit.render(getMatrix());
		m_fuselage.render(getMatrix());
		m_leftEngine.render(getMatrix());
		m_rightEngine.render(getMatrix());
		m_leftNozzle.render(getMatrix());
		m_rightNozzle.render(getMatrix());
		m_leftWing.render(getMatrix());
		m_rightWing.render(getMatrix());
		m_leftVStab.render(getMatrix());
		m_rightVStab.render(getMatrix());
		m_leftElevator.render(getMatrix());
		m_rightElevator.render(getMatrix());
		m_leftRudder.render(getMatrix());
		m_rightRudder.render(getMatrix());
		m_leftAileron.render(getMatrix());
		m_rightAileron.render(getMatrix());
	}

	void JW1::renderLights() const
	{ }
};
