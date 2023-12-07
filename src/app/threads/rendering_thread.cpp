#include "app/threads/rendering_thread.hpp"

#include "app/controller_type.hpp"
#include "app/game_mode.hpp"
#include "app/threads/network_thread.hpp"
#include "app/window_payload.hpp"
#include "common/airplane_type_name.hpp"
#include "common/sync/user_input.hpp"
#include "graphics/maps/map_name.hpp"
#include "graphics/time.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <memory>
#include <semaphore>
#include <string>

namespace App
{
	RenderingThread::RenderingThread(ControllerType controllerType) :
		m_windowInput{m_window, controllerType}
	{ }

	void RenderingThread::start(GameMode gameMode, Common::AirplaneTypeName airplaneTypeName,
		Graphics::MapName mapName, const std::string& ipAddress, int port)
	{
		std::binary_semaphore semaphore{0};
		NetworkThread networkThread{semaphore, gameMode, ipAddress, port, m_ownInput,
			m_renderingBuffer};
		initializeWindow();
		semaphore.acquire();
		m_renderingBuffer->initialize(airplaneTypeName, mapName);
		mainLoop();
		networkThread.stop();
		networkThread.join();
		glfwTerminate();
	}

	void RenderingThread::mainLoop()
	{
		Graphics::Time time;
		time.initialize();
		while (!glfwWindowShouldClose(m_window))
		{
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
		static constexpr int initialWindowWidth = 1900;
		static constexpr int initialWindowHeight = 950;
		m_windowPayload.aspectRatio = static_cast<float>(initialWindowWidth) / initialWindowHeight;
		m_window = glfwCreateWindow(static_cast<int>(initialWindowWidth),
			static_cast<int>(initialWindowHeight), "Plane", nullptr, nullptr);
		glfwSetWindowUserPointer(m_window, &m_windowPayload);
		static constexpr int initialWindowPositionX = 0;
		static constexpr int initialWindowPositionY = 38;
		glfwSetWindowPos(m_window, initialWindowPositionX, initialWindowPositionY);
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
		App::WindowPayload* windowPayload = (App::WindowPayload*)glfwGetWindowUserPointer(window);
		windowPayload->aspectRatio = static_cast<float>(width) / height;
		glViewport(0, 0, width, height);
	}

	void RenderingThread::processInput()
	{
		const Common::UserInput& ownInput = m_windowInput.getCurrentInput();
		m_ownInput.setOwnInput(ownInput);
	}
};
