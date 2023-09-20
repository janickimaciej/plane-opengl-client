#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/window_payload.hpp"
#include "scenes/airport_scene.hpp"
#include "scenes/scene.hpp"
#include "time.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>

GLFWwindow* graphicsInit(unsigned int initWindowWidth, unsigned int initWindowHeight,
	WindowPayload& windowPayload);
void resizeWindow(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	static constexpr unsigned int initialWindowWidth = 1500;
	static constexpr unsigned int initialWindowHeight = 800;
	WindowPayload windowPayload{};
	GLFWwindow* window = graphicsInit(initialWindowWidth, initialWindowHeight, windowPayload);

	ShaderProgram surfaceShaderProgram{SH_SURFACE_VERTEX, SH_SURFACE_FRAGMENT};
	ShaderProgram lightShaderProgram{SH_LIGHT_VERTEX, SH_LIGHT_FRAGMENT};

	Scene* airportScene = new AirportScene{surfaceShaderProgram, lightShaderProgram,
		(float)initialWindowWidth/initialWindowHeight};
	windowPayload.scene = airportScene;
	
	Time::initializeTime();
	while (!glfwWindowShouldClose(window))
	{
		Time::updateTime();
		processInput(window);
		airportScene->update();
		airportScene->render();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	delete airportScene;
	glfwTerminate();
	return 0;
}

GLFWwindow* graphicsInit(unsigned int initWindowWidth, unsigned int initWindowHeight,
	WindowPayload& windowPayload)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow((int)initWindowWidth, (int)initWindowHeight, "Plane",
		nullptr, nullptr);
	glfwSetWindowUserPointer(window, &windowPayload);
	static constexpr int initWindowPositionX = 0;
	static constexpr int initWindowPositionY = 38;
	glfwSetWindowPos(window, initWindowPositionX, initWindowPositionY);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glEnable(GL_DEPTH_TEST);
	return window;
}

void resizeWindow(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0)
	{
		return;
	}

	WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);
	windowPayload->scene->setAspectRatio((float)width/height);
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlYaw(-1);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlYaw(1);
	}
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlPitch(-1);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlPitch(1);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlRoll(-1);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlRoll(1);
	}
	
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.2f);
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.3f);
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.4f);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.5f);
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.6f);
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.7f);
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.8f);
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		windowPayload->scene->ctrlThrust(0.9f);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		windowPayload->scene->setActiveCamera(1);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		windowPayload->scene->setActiveCamera(2);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		windowPayload->scene->setActiveCamera(3);
	}
}
