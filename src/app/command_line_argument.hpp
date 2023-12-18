#pragma once

#include <cstddef>

namespace App
{
	inline constexpr int multiplayerArgumentCount = 9;
	inline constexpr int singleplayerArgumentCount = 5;

	enum class CommandLineArgument
	{
		programName,
		gameMode,
		controllerType,
		airplaneType,
		map,
		serverIPAddress,
		serverPort,
		networkThreadPort,
		physicsThreadPort
	};

	std::size_t toSizeT(CommandLineArgument commandLineArgument);
};
