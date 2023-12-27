#include "graphics/models/airplanes/airplane.hpp"

#include "common/airplane_ctrl.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/asset_manager.hpp"
#include "graphics/lights/spot_light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/models/airplanes/jw1.hpp"
#include "graphics/models/airplanes/mustang.hpp"
#include "graphics/path.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	std::unique_ptr<Airplane> Airplane::createAirplane(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, AssetManager<const Mesh>& meshManager,
		AssetManager<const Texture>& textureManager, Common::AirplaneTypeName airplaneTypeName)
	{
		switch (airplaneTypeName)
		{
		case Common::AirplaneTypeName::mustang:
			return std::make_unique<Mustang>(surfaceShaderProgram, lightShaderProgram, meshManager,
				textureManager);

		case Common::AirplaneTypeName::jw1:
			return std::make_unique<JW1>(surfaceShaderProgram, lightShaderProgram, meshManager,
				textureManager);
		}
		return nullptr;
	}

	Airplane::Airplane(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram) :
		Model{surfaceShaderProgram, lightShaderProgram}
	{ }
};
