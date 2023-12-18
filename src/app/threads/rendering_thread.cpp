#include "app/threads/rendering_thread.hpp"

#include "app/controller_type.hpp"
#include "app/exit_code.hpp"
#include "app/exit_signal.hpp"
#include "app/game_mode.hpp"
#include "app/threads/network_thread.hpp"
#include "app/window_payload.hpp"
#include "common/airplane_type_name.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/time.hpp"
#include "physics/player_input.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <memory>
#include <semaphore>
#include <string>

namespace App
{
	RenderingThread::RenderingThread(ExitSignal& exitSignal, ControllerType controllerType) :
		m_exitSignal{exitSignal},
		m_windowInput{m_window, controllerType}
	{ }

	void RenderingThread::start(GameMode gameMode, Common::AirplaneTypeName airplaneTypeName,
		Graphics::MapName mapName, const std::string& serverIPAddress, int serverPort,
		int networkThreadPort, int physicsThreadPort)
	{
		NetworkThread networkThread{m_exitSignal, gameMode, airplaneTypeName, serverIPAddress,
			serverPort, networkThreadPort, physicsThreadPort, m_ownInput, m_renderingBuffer};
		initializeWindow();
		m_exitSignal.acquireRenderingThreadSemaphore();
		if (!m_exitSignal.shouldStop())
		{
			m_renderingBuffer->initialize(airplaneTypeName, mapName);
			mainLoop();
			glfwTerminate();
		}
		networkThread.join();
	}

	void RenderingThread::mainLoop()
	{
		Graphics::Time time;
		time.initialize();
		while (!m_exitSignal.shouldStop())
		{
			if (glfwWindowShouldClose(m_window))
			{
				m_exitSignal.exit(ExitCode::ok);
				break;
			}
			time.update();
			processInput();
			m_renderingBuffer->updateAndRenderScene(m_windowPayload.aspectRatio);
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}
	}

	void RenderingThread::initializeWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		const int initialWindowWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2; //tmp
		//const int initialWindowWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width; //tmpc
		const int initialWindowHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
		m_windowPayload.aspectRatio = static_cast<float>(initialWindowWidth) / initialWindowHeight;
		const std::string windowTitle = "plane-opengl-client";
		m_window = glfwCreateWindow(initialWindowWidth, initialWindowHeight, windowTitle.c_str(),
			/*glfwGetPrimaryMonitor()*/nullptr, nullptr); //tmpc
		glfwSetWindowUserPointer(m_window, &m_windowPayload);
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, resizeWindow);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glEnable(GL_DEPTH_TEST);
	}

	void RenderingThread::resizeWindow(GLFWwindow* window, int width, int height)
	{
		if (width == 0 || height == 0)
		{
			return;
		}
		WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);
		windowPayload->aspectRatio = static_cast<float>(width) / height;
		glViewport(0, 0, width, height);
	}

	void RenderingThread::processInput()
	{
		const Physics::PlayerInput& ownInput = m_windowInput.getCurrentInput();
		m_ownInput.setOwnInput(ownInput);
	}
};
