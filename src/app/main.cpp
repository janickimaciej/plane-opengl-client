#include "app/threads/rendering_thread.hpp"
#include "app/command_line_argument.hpp"
#include "app/controller_type.hpp"
#include "app/exit_code.hpp"
#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/maps/map_name.hpp"

#include <cstddef>
#include <semaphore>
#include <string>

namespace App
{
	bool parseArguments(int argc, char** argv, GameMode& gameMode,
		ControllerType& controllerType, Common::AirplaneTypeName& airplaneTypeName,
		Graphics::MapName& mapName, std::string& serverIPAddress, int& serverPort,
		int& networkThreadPort, int& physicsThreadPort);
	bool isValidIPAddress(const std::string& serverIPAddress);
};

int main(int argc, char** argv)
{
	using namespace App;

	GameMode gameMode{};
	ControllerType controllerType{};
	Common::AirplaneTypeName airplaneTypeName{};
	Graphics::MapName mapName{};
	std::string serverIPAddress{};
	int serverPort{};
	int networkThreadPort{};
	int physicsThreadPort{};

	if (!parseArguments(argc, argv, gameMode, controllerType, airplaneTypeName, mapName,
		serverIPAddress, serverPort, networkThreadPort, physicsThreadPort))
	{
		return toInt(ExitCode::badArguments);
	}

	ExitSignal exitSignal{};
	RenderingThread renderingThread{exitSignal, controllerType};
	renderingThread.start(gameMode, airplaneTypeName, mapName, serverIPAddress, serverPort,
		networkThreadPort, physicsThreadPort);

	return toInt(exitSignal.getExitCode());
}

namespace App
{
	bool parseArguments(int argc, char** argv, GameMode& gameMode,
		ControllerType& controllerType, Common::AirplaneTypeName& airplaneTypeName,
		Graphics::MapName& mapName, std::string& serverIPAddress, int& serverPort,
		int& networkThreadPort, int& physicsThreadPort)
	{
		if (argc < 2)
		{
			return false;
		}

		int gameModeIndex = std::stoi(argv[toSizeT(CommandLineArgument::gameMode)]);
		if (gameModeIndex < 0 || gameModeIndex > 1)
		{
			return false;
		}
		gameMode = static_cast<GameMode>(gameModeIndex);
	
		if (!((gameMode == GameMode::multiplayer && argc == multiplayerArgumentCount) ||
			(gameMode == GameMode::singleplayer && argc == singleplayerArgumentCount)))
		{
			return false;
		}

		int controllerTypeIndex =
			std::stoi(argv[toSizeT(CommandLineArgument::controllerType)]);
		if (controllerTypeIndex < 0 || controllerTypeIndex >= controllerTypeCount)
		{
			return false;
		}
		controllerType = static_cast<ControllerType>(controllerTypeIndex);

		int airplaneTypeNameIndex =
			std::stoi(argv[toSizeT(CommandLineArgument::airplaneType)]);
		if (airplaneTypeNameIndex < 0 || airplaneTypeNameIndex >= Common::airplaneTypeCount)
		{
			return false;
		}
		airplaneTypeName = static_cast<Common::AirplaneTypeName>(airplaneTypeNameIndex);

		int mapNameIndex = std::stoi(argv[toSizeT(CommandLineArgument::map)]);
		if (mapNameIndex < 0 || mapNameIndex >= Graphics::mapCount)
		{
			return false;
		}
		mapName = static_cast<Graphics::MapName>(mapNameIndex);

		if (gameMode == GameMode::singleplayer)
		{
			return true;
		}

		serverIPAddress = argv[toSizeT(CommandLineArgument::serverIPAddress)];
		if (!isValidIPAddress(serverIPAddress))
		{
			return false;
		}

		constexpr int minPortValue = 0;
		constexpr int maxPortValue = 1 << 16;

		serverPort = std::stoi(argv[toSizeT(CommandLineArgument::serverPort)]);
		if (serverPort < minPortValue || serverPort >= maxPortValue)
		{
			return false;
		}

		networkThreadPort = std::stoi(argv[toSizeT(CommandLineArgument::networkThreadPort)]);
		if (networkThreadPort < minPortValue || networkThreadPort >= maxPortValue)
		{
			return false;
		}

		physicsThreadPort = std::stoi(argv[toSizeT(CommandLineArgument::physicsThreadPort)]);
		if (physicsThreadPort < minPortValue || physicsThreadPort >= maxPortValue)
		{
			return false;
		}

		return true;
	}

	bool isValidIPAddress(const std::string& serverIPAddress)
	{
		int fieldIndex = 0;
		std::string fieldString{};
		for (std::size_t i = 0; i < serverIPAddress.size(); ++i)
		{
			if (serverIPAddress[i] < '0' || serverIPAddress[i] > '9')
			{
				if (!fieldString.empty() && serverIPAddress[i] == '.')
				{
					int fieldInt = std::stoi(fieldString);
					constexpr int maxFieldValue = 256;
					if (fieldInt >= maxFieldValue)
					{
						return false;
					}
					fieldString.clear();
					++fieldIndex;
				}
				else
				{
					return false;
				}
			}
			else
			{
				fieldString.push_back(serverIPAddress[i]);
			}
		}

		if (fieldIndex == 3 && !fieldString.empty())
		{
			int fieldInt = std::stoi(fieldString);
			constexpr int maxFieldValue = 256;
			if (fieldInt >= maxFieldValue)
			{
				return false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
};
