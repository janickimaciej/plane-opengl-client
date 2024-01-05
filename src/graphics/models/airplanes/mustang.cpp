#include "graphics/models/airplanes/mustang.hpp"

#include "common/airplane_centers_of_mass.hpp"
#include "common/airplane_ctrl.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/meshes/mesh.hpp"
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

	const Material texturedMetal{glm::vec3{1, 1, 1}, 0.75, 0.5, 30, true};
	const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.5, 30, true};
	const Material rubber{glm::vec3{0.1, 0.1, 0.1}, 0.75, 0, 1, false};
	const Material whiteLightGlass{glm::vec3{1, 1, 1}, 1, 1, 1, false};

	Mustang::Mustang(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		Airplane{surfaceShaderProgram, lightShaderProgram},
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
		constexpr float lightsPositionXAbs = 2.14f;
		constexpr float lightsPositionY = -0.474f;
		constexpr float lightsPositionZ = 2.938f;
		m_leftLight.translate(glm::vec3{lightsPositionXAbs, lightsPositionY, lightsPositionZ});
		m_rightLight.translate(glm::vec3{-lightsPositionXAbs, lightsPositionY, lightsPositionZ});

		constexpr glm::vec3 nosePosition = -Common::airplaneCentersOfMass[
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
