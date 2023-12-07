#include "app/threads/rendering_thread.hpp"
#include "app/controller_type.hpp"
#include "app/game_mode.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/maps/map_name.hpp"

#include <string>

bool parseArguments(int argc, char** argv, App::GameMode& gameMode,
	App::ControllerType& controllerType, Common::AirplaneTypeName& airplaneTypeName,
	Graphics::MapName& mapName, std::string& ipAddress, int& port);
bool isValidIPAddress(const std::string& ipAddress);

int main(int argc, char** argv)
{
	App::GameMode gameMode{};
	App::ControllerType controllerType{};
	Common::AirplaneTypeName airplaneTypeName{};
	Graphics::MapName mapName{};
	std::string ipAddress{};
	int port{};

	if (!parseArguments(argc, argv, gameMode, controllerType, airplaneTypeName, mapName, ipAddress,
		port))
	{
		return 1;
	}

	App::RenderingThread renderingThread{controllerType};
	renderingThread.start(gameMode, airplaneTypeName, mapName, ipAddress, port);

	return 0;
}

bool parseArguments(int argc, char** argv, App::GameMode& gameMode,
	App::ControllerType& controllerType, Common::AirplaneTypeName& airplaneTypeName,
	Graphics::MapName& mapName, std::string& ipAddress, int& port)
{
	if (argc < 2)
	{
		return false;
	}

	int gameModeIndex = std::stoi(argv[1]);
	if (gameModeIndex < 0 || gameModeIndex > 1)
	{
		return false;
	}
	gameMode = static_cast<App::GameMode>(gameModeIndex);
	
	constexpr int multiplayerArgumentCount = 7;
	constexpr int singleplayerArgumentCount = 5;
	if (!((gameMode == App::GameMode::multiplayer && argc == multiplayerArgumentCount) ||
		(gameMode == App::GameMode::singleplayer && argc == singleplayerArgumentCount)))
	{
		return false;
	}

	int controllerTypeIndex = std::stoi(argv[2]);
	if (controllerTypeIndex < 0 || controllerTypeIndex >= App::controllerTypeCount)
	{
		return false;
	}
	controllerType = static_cast<App::ControllerType>(controllerTypeIndex);

	int airplaneTypeNameIndex = std::stoi(argv[3]);
	if (airplaneTypeNameIndex < 0 || airplaneTypeNameIndex >= Common::airplaneTypeCount)
	{
		return false;
	}
	airplaneTypeName = static_cast<Common::AirplaneTypeName>(airplaneTypeNameIndex);

	int mapNameIndex = std::stoi(argv[4]);
	if (mapNameIndex < 0 || mapNameIndex >= Graphics::mapCount)
	{
		return false;
	}
	mapName = static_cast<Graphics::MapName>(mapNameIndex);

	if (gameMode == App::GameMode::singleplayer)
	{
		return true;
	}

	ipAddress = argv[5];
	if (!isValidIPAddress(ipAddress))
	{
		return false;
	}

	port = std::stoi(argv[6]);
	constexpr int minPortValue = 0;
	constexpr int maxPortValue = 1 << 16;
	if (port < minPortValue || port >= maxPortValue)
	{
		return false;
	}

	return true;
}

bool isValidIPAddress(const std::string& ipAddress)
{
	int fieldIndex = 0;
	std::string fieldString{};
	for (unsigned int i = 0; i < ipAddress.size(); ++i)
	{
		if (ipAddress[i] < '0' || ipAddress[i] > '9')
		{
			if (!fieldString.empty() && ipAddress[i] == '.')
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
			fieldString.push_back(ipAddress[i]);
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
