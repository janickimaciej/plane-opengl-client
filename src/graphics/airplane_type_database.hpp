#pragma once

#include "common/airplane_database.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/airplane_type.hpp"
#include "graphics/paths.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Graphics
{
	inline const std::array<AirplaneType, Common::airplaneTypeCount> airplaneTypeDatabase
	{
		{
			-Common::airplaneCenterOfMassDatabase[
				static_cast<std::size_t>(Common::AirplaneTypeName::mustang)],
			T_CAMO,
			SM_AIRPLANE_CAP,
			SM_AIRPLANE_PROPELLER,
			SM_AIRPLANE_BODY,
			SM_AIRPLANE_JOINS,
			SM_AIRPLANE_TIRES,
			SM_AIRPLANE_LIGHT
		}
	};
};
