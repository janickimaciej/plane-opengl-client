#pragma once

#include <cstddef>

namespace App
{
	constexpr int multiplayerArgumentCount = 7;
	constexpr int singleplayerArgumentCount = 5;

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
