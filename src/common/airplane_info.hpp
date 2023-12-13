#pragma once

#include "common/airplane_ctrl.hpp"
#include "common/airplane_type_name.hpp"
#include "common/state.hpp"

namespace Common
{
	struct AirplaneInfo
	{
		State state{};
		AirplaneCtrl airplaneCtrl{};
		AirplaneTypeName airplaneTypeName{};
	};
};
