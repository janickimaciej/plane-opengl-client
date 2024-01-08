#pragma once

#include "app/controller_type.hpp"
#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/own_input.hpp"
#include "app/threads/network_thread.hpp"
#include "app/window_input.hpp"
#include "app/window_payload.hpp"
#include "common/airplane_type_name.hpp"
#include "common/map_name.hpp"
#include "graphics/rendering_buffer.hpp"

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
