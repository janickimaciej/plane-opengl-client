#include "graphics/models/model.hpp"

#include "common/transformable.hpp"
#include "common/state.hpp"
#include "graphics/shaderProgram.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	glm::mat4 Model::getModelMatrix() const
	{
		return getMatrix();
	}

	glm::vec3 Model::getPosition() const
	{
		return getState().position;
	}

	void Model::scale(float scaleRatio)
	{
		Transformable::scale(scaleRatio);
	}
};
