#pragma once

#include "app/controllerType.hpp"
#include "app/exitSignal.hpp"
#include "app/gameMode.hpp"
#include "app/ownInput.hpp"
#include "app/threads/networkThread.hpp"
#include "app/windowInput.hpp"
#include "app/windowPayload.hpp"
#include "common/airplaneTypeName.hpp"
#include "common/mapName.hpp"
#include "graphics/renderingBuffer.hpp"

#include <glfw/glfw3.h>

#include <memory>
#include <string>

namespace App
{
	class RenderingThread
	{
	public:
		RenderingThread(ExitSignal& exitSignal, ControllerType controllerType);
		void start(GameMode gameMode, Common::AirplaneTypeName airplaneTypeName,
			Common::MapName mapName, const std::string& serverIPAddress,
			int serverNetworkThreadPort, int serverPhysicsThreadPort, int clientNetworkThreadPort,
			int clientPhysicsThreadPort);

	private:
		ExitSignal& m_exitSignal;

		GLFWwindow* m_window{};
		WindowPayload m_windowPayload{};
		std::unique_ptr<Graphics::RenderingBuffer> m_renderingBuffer{};

		WindowInput m_windowInput;
		OwnInput m_ownInput{};

		void mainLoop();
		void initializeWindow();
		static void resizeWindow(GLFWwindow* window, int width, int height);
		void processInput();
	};
};
