#pragma once

#include <cstddef>

namespace App
{
	inline constexpr int multiplayerArgumentCount = 7;
	inline constexpr int singleplayerArgumentCount = 5;

	enum class CommandLineArgument
	{
		programName,
		gameMode,
		controllerType,
		airplaneType,
		map,
		ipAddress,
		port
	};

	std::size_t toSizeT(CommandLineArgument commandLineArgument);
};
