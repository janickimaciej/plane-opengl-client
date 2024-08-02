#include "app/threads/renderingThread.hpp"
#include "app/commandLineArgument.hpp"
#include "app/controllerType.hpp"
#include "app/exitCode.hpp"
#include "app/exitSignal.hpp"
#include "app/gameMode.hpp"
#include "common/airplaneTypeName.hpp"
#include "common/mapName.hpp"

#include <cstddef>
#include <semaphore>
#include <string>

namespace App
{
	bool parseArguments(int argc, char** argv, GameMode& gameMode,
		ControllerType& controllerType, Common::AirplaneTypeName& airplaneTypeName,
		Common::MapName& mapName, std::string& serverIPAddress, int& serverNetworkThreadPort,
		int& serverPhysicsThreadPort, int& clientNetworkThreadPort, int& clientPhysicsThreadPort);
	bool isValidIPAddress(const std::string& serverIPAddress);
};

int main(int argc, char** argv)
{
	using namespace App;

	GameMode gameMode{};
	ControllerType controllerType{};
	Common::AirplaneTypeName airplaneTypeName{};
	Common::MapName mapName{};
	std::string serverIPAddress{};
	int serverNetworkThreadPort{};
	int serverPhysicsThreadPort{};
	int clientNetworkThreadPort{};
	int clientPhysicsThreadPort{};

	if (!parseArguments(argc, argv, gameMode, controllerType, airplaneTypeName, mapName,
		serverIPAddress, serverNetworkThreadPort, serverPhysicsThreadPort, clientNetworkThreadPort,
		clientPhysicsThreadPort))
	{
		return toInt(ExitCode::badArguments);
	}

	ExitSignal exitSignal{};
	RenderingThread renderingThread{exitSignal, controllerType};
	renderingThread.start(gameMode, airplaneTypeName, mapName, serverIPAddress,
		serverNetworkThreadPort, serverPhysicsThreadPort, clientNetworkThreadPort,
		clientPhysicsThreadPort);

	return toInt(exitSignal.getExitCode());
}

namespace App
{
	bool parseArguments(int argc, char** argv, GameMode& gameMode,
		ControllerType& controllerType, Common::AirplaneTypeName& airplaneTypeName,
		Common::MapName& mapName, std::string& serverIPAddress, int& serverNetworkThreadPort,
		int& serverPhysicsThreadPort, int& clientNetworkThreadPort, int& clientPhysicsThreadPort)
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
		if (mapNameIndex < 0 || mapNameIndex >= Common::mapCount)
		{
			return false;
		}
		mapName = static_cast<Common::MapName>(mapNameIndex);

		if (gameMode == GameMode::singleplayer)
		{
			return true;
		}

		serverIPAddress = argv[toSizeT(CommandLineArgument::serverIPAddress)];
		if (!isValidIPAddress(serverIPAddress))
		{
			return false;
		}

		static constexpr int minPortValue = 0;
		static constexpr int maxPortValue = 1 << 16;

		serverNetworkThreadPort =
			std::stoi(argv[toSizeT(CommandLineArgument::serverNetworkThreadPort)]);
		if (serverNetworkThreadPort < minPortValue || serverNetworkThreadPort >= maxPortValue)
		{
			return false;
		}

		serverPhysicsThreadPort =
			std::stoi(argv[toSizeT(CommandLineArgument::serverPhysicsThreadPort)]);
		if (serverPhysicsThreadPort < minPortValue || serverPhysicsThreadPort >= maxPortValue)
		{
			return false;
		}

		clientNetworkThreadPort =
			std::stoi(argv[toSizeT(CommandLineArgument::clientNetworkThreadPort)]);
		if (clientNetworkThreadPort < minPortValue || clientNetworkThreadPort >= maxPortValue)
		{
			return false;
		}

		clientPhysicsThreadPort =
			std::stoi(argv[toSizeT(CommandLineArgument::clientPhysicsThreadPort)]);
		if (clientPhysicsThreadPort < minPortValue || clientPhysicsThreadPort >= maxPortValue)
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
					static constexpr int maxFieldValue = 256;
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
			static constexpr int maxFieldValue = 256;
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
