#pragma once

#include <cstddef>

namespace App
{
	inline constexpr int multiplayerArgumentCount = 10;
	inline constexpr int singleplayerArgumentCount = 5;

	enum class CommandLineArgument
	{
		programName,
		gameMode,
		controllerType,
		airplaneType,
		map,
		serverIPAddress,
		serverNetworkThreadPort,
		serverPhysicsThreadPort,
		clientNetworkThreadPort,
		clientPhysicsThreadPort
	};

	std::size_t toSizeT(CommandLineArgument commandLineArgument);
};
