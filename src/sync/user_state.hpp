#pragma once

#include "database/airplane_database.hpp"
#include "state.hpp"

struct UserState
{
	int hp{};
	State state{};
	AirplaneTypeName airplaneTypeName;
};
