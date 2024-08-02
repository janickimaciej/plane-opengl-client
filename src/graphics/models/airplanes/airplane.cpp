#include "graphics/models/airplanes/airplane.hpp"

#include "common/airplaneCtrl.hpp"
#include "common/airplaneTypeName.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/models/airplanes/jw1.hpp"
#include "graphics/models/airplanes/mustang.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderProgram.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	std::unique_ptr<Airplane> Airplane::createAirplane(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<std::string, const Texture>& textureManager,
		Common::AirplaneTypeName airplaneTypeName)
	{
		switch (airplaneTypeName)
		{
			case Common::AirplaneTypeName::mustang:
				return std::make_unique<Mustang>(surfaceShaderProgram, lightShaderProgram,
					fileMeshManager, textureManager);

			case Common::AirplaneTypeName::jw1:
				return std::make_unique<JW1>(surfaceShaderProgram, lightShaderProgram, fileMeshManager,
					textureManager);
		}
		return nullptr;
	}

	int Airplane::getHP() const
	{
		return m_hp;
	}

	void Airplane::setHP(int hp)
	{
		m_hp = hp;
	}
};
