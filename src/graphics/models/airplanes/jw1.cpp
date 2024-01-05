#include "graphics/models/airplanes/jw1.hpp"

#include "common/airplane_centers_of_mass.hpp"
#include "common/airplane_ctrl.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
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
	const std::string rightNozzleGlassPath = meshPath(modelName, "rightNozzleGlass");
	const std::string rightWingPath = meshPath(modelName, "rightWing");
	const std::string rightVStabPath = meshPath(modelName, "rightVStab");
	const std::string rightElevatorPath = meshPath(modelName, "rightElevator");
	const std::string rightRudderPath = meshPath(modelName, "rightRudder");
	const std::string rightAileronPath = meshPath(modelName, "rightAileron");

	const std::string camoPath = texturePath(modelName, "camo");
	const std::string nozzleGlassPath = texturePath(modelName, "nozzleGlass");

	constexpr float lightsAttenuationQuadratic = 0.0001f;
	constexpr float lightsAttenuationLinear = 0.0005f;
	constexpr float lightsAttenuationConstant = 1;
	constexpr glm::vec3 lightsColor{1, 1, 1};
	
	const Material texturedMetal{glm::vec3{1, 1, 1}, 0.2f, 0.2f, 30, true};
	const Material darkMetal{glm::vec3{0.4, 0.4, 0.4}, 0.2f, 0.2f, 30, true};
	const Material defaultNozzleGlass{glm::vec3{0, 0, 0}, 1, 1, 1, false};
	const Material blackGlass{glm::vec3{0, 0, 0}, 0.75, 1, 50, false};
	
	JW1::JW1(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		Airplane{surfaceShaderProgram, lightShaderProgram},
		m_cone{surfaceShaderProgram, fileMeshManager.get(conePath), texturedMetal,
			textureManager.get(camoPath)},
		m_gun{surfaceShaderProgram, fileMeshManager.get(gunPath), texturedMetal,
			textureManager.get(camoPath)},
		m_cockpit{surfaceShaderProgram, fileMeshManager.get(cockpitPath), blackGlass},
		m_fuselage{surfaceShaderProgram, fileMeshManager.get(fuselagePath), texturedMetal,
			textureManager.get(camoPath)},
		m_leftEngine{surfaceShaderProgram, fileMeshManager.get(rightEnginePath), texturedMetal,
			textureManager.get(camoPath)},
		m_rightEngine{surfaceShaderProgram, fileMeshManager.get(rightEnginePath), texturedMetal,
			textureManager.get(camoPath)},
		m_leftNozzle{surfaceShaderProgram, fileMeshManager.get(rightNozzlePath), darkMetal},
		m_rightNozzle{surfaceShaderProgram, fileMeshManager.get(rightNozzlePath), darkMetal},
		m_leftNozzleGlass{lightShaderProgram, fileMeshManager.get(rightNozzleGlassPath),
			defaultNozzleGlass, textureManager.get(nozzleGlassPath)},
		m_rightNozzleGlass{lightShaderProgram, fileMeshManager.get(rightNozzleGlassPath),
			defaultNozzleGlass, textureManager.get(nozzleGlassPath)},
		m_leftWing{surfaceShaderProgram, fileMeshManager.get(rightWingPath), texturedMetal,
			textureManager.get(camoPath)},
		m_rightWing{surfaceShaderProgram, fileMeshManager.get(rightWingPath), texturedMetal,
			textureManager.get(camoPath)},
		m_leftVStab{surfaceShaderProgram, fileMeshManager.get(rightVStabPath), texturedMetal,
			textureManager.get(camoPath)},
		m_rightVStab{surfaceShaderProgram, fileMeshManager.get(rightVStabPath), texturedMetal,
			textureManager.get(camoPath)},
		m_leftElevator{surfaceShaderProgram, fileMeshManager.get(rightElevatorPath), texturedMetal,
			textureManager.get(camoPath)},
		m_rightElevator{surfaceShaderProgram, fileMeshManager.get(rightElevatorPath), texturedMetal,
			textureManager.get(camoPath)},
		m_leftRudder{surfaceShaderProgram, fileMeshManager.get(rightRudderPath), texturedMetal,
			textureManager.get(camoPath)},
		m_rightRudder{surfaceShaderProgram, fileMeshManager.get(rightRudderPath), texturedMetal,
			textureManager.get(camoPath)},
		m_leftAileron{surfaceShaderProgram, fileMeshManager.get(rightAileronPath), texturedMetal,
			textureManager.get(camoPath)},
		m_rightAileron{surfaceShaderProgram, fileMeshManager.get(rightAileronPath), texturedMetal,
			textureManager.get(camoPath)}
	{
		m_leftEngine.mirrorX();
		m_leftNozzle.mirrorX();
		m_leftNozzleGlass.mirrorX();
		m_leftWing.mirrorX();
		m_leftVStab.mirrorX();
		m_leftElevator.mirrorX();
		m_leftRudder.mirrorX();
		m_leftAileron.mirrorX();
		
		m_leftElevator.translate(glm::vec3{0, 0, 16.6});
		m_rightElevator.translate(glm::vec3{0, 0, 16.6});
		m_leftRudder.translate(glm::vec3{-1.375, 0.533, 18.92});
		m_rightRudder.translate(glm::vec3{1.375, 0.533, 18.92});
		m_leftAileron.translate(glm::vec3{-4.107, 0.535, 14.57});
		m_rightAileron.translate(glm::vec3{4.107, 0.535, 14.57});

		constexpr glm::vec3 nosePosition = -Common::airplaneCentersOfMass[
			toSizeT(Common::AirplaneTypeName::jw1)];
		m_cone.translate(nosePosition);
		m_gun.translate(nosePosition);
		m_cockpit.translate(nosePosition);
		m_fuselage.translate(nosePosition);
		m_leftEngine.translate(nosePosition);
		m_rightEngine.translate(nosePosition);
		m_leftNozzle.translate(nosePosition);
		m_rightNozzle.translate(nosePosition);
		m_leftNozzleGlass.translate(nosePosition);
		m_rightNozzleGlass.translate(nosePosition);
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
	{ }

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

		static constexpr glm::vec3 nozzleMaxColor{1, 0.8, 0};
		Material nozzleGlass{airplaneCtrl.thrustRelative * nozzleMaxColor, 1, 1, 1, false};
		m_leftNozzleGlass.setMaterial(nozzleGlass);
		m_rightNozzleGlass.setMaterial(nozzleGlass);
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
	{
		m_leftNozzleGlass.render(getMatrix());
		m_rightNozzleGlass.render(getMatrix());
	}
};
