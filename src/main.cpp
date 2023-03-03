#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader_program.hpp"
#include "structs/window_payload.hpp"
#include "time.hpp"
#include "paths.hpp"

constexpr unsigned int initialWindowWidth = 1500;
constexpr unsigned int initialWindowHeight = 800;

GLFWwindow* initialize(unsigned int width, unsigned int height, WindowPayload* windowPayload);
void resizeWindow(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	WindowPayload windowPayload;
	GLFWwindow* window = initialize(initialWindowWidth, initialWindowHeight, &windowPayload);

	ShaderProgram surfaceShaderProgram = ShaderProgram(SH_SURFACE_VERTEX, SH_SURFACE_FRAGMENT);
	ShaderProgram lightShaderProgram = ShaderProgram(SH_LIGHT_VERTEX, SH_LIGHT_FRAGMENT);

	AirportScene airportScene = AirportScene(surfaceShaderProgram, lightShaderProgram,
		(float)initialWindowWidth/initialWindowHeight);
	windowPayload.airportScene = &airportScene;
	
	Time::initializeTime();
	while(!glfwWindowShouldClose(window)) {
		Time::updateTime();
		processInput(window);
		airportScene.update();
		airportScene.render();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* initialize(unsigned int width, unsigned int height, WindowPayload* windowPayload) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Plane", nullptr, nullptr);
	glfwSetWindowUserPointer(window, windowPayload);
	glfwSetWindowPos(window, 0, 38);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glEnable(GL_DEPTH_TEST);
	return window;
}

void resizeWindow(GLFWwindow* window, int width, int height) {
	if(width == 0 || height == 0) {
		return;
	}

	WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);
	windowPayload->airportScene->setAspectRatio((float)width/height);
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		windowPayload->airportScene->setActiveCamera(1);
	}
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		windowPayload->airportScene->setActiveCamera(2);
	}
	if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		windowPayload->airportScene->setActiveCamera(3);
	}

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlMoveAlongZNegative();
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlMoveAlongZPositive();
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlYawNegative();
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlYawPositive();
	}
	
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlPitchNegative();
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlPitchPositive();
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlRollNegative();
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		windowPayload->airportScene->ctrlRollPositive();
	}
}
