#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader_program.hpp"
#include "global_shading.hpp"
#include "mesh.hpp"
#include "models/airport.hpp"
#include "models/airplane.hpp"
#include "models/zeppelin.hpp"
#include "models/airport.hpp"
#include "cameras/model_camera.hpp"
#include "cameras/tracking_camera.hpp"
#include "structs/window_payload.hpp"
#include "time.hpp"
#include "day_night_cycle.hpp"
#include "models/directional_light_model.hpp"
#include "paths.hpp"

constexpr float velocity = 50;
constexpr float angVelocityDeg = 60;
constexpr float propellerAngVelocityDeg = 360;
constexpr float lightsAngVelocityDeg = 10;
constexpr int airplanesCount = 5;

unsigned int gWidth = 1500;
unsigned int gHeight = 800;

GLFWwindow* initialize(unsigned int width, unsigned int height, WindowPayload* windowPayload);
void resizeWindow(GLFWwindow* window, int width, int height);
void setScene(std::vector<Airplane>& airplanes, Zeppelin& zeppelin, DirectionalLightModel& moon);
void setCameras(ModelCamera& airplaneCamera, TrackingCamera& trackingCamera,
	PerspectiveCamera& stationaryCamera);
void processInput(GLFWwindow* window);
float c2f(unsigned char color);

int main() {
	WindowPayload windowPayload;
	GLFWwindow* window = initialize(gWidth, gHeight, &windowPayload);

	GlobalShading::setAmbient(0.2);
	GlobalShading::setFogGradient(1.5);
	
	Material defaultMaterial = Material(glm::vec3(1, 0, 0), 0.75, 0.25, 10); // dummy color
	Material concrete = Material(glm::vec3(1, 0, 0), 0.75, 0, 10); // dummy color
	Material metal = Material(glm::vec3(0.25, 0.25, 0.25), 0.75, 0.25, 10);
	Material rubber = Material(glm::vec3(0.1, 0.1, 0.1), 0.75, 0.25, 10);
	Material zeppelinCanvas = Material(glm::vec3(0.9, 0.9, 0.9), 0.75, 0.25, 10);
	Material whiteLightGlass = Material(glm::vec3(1, 1, 1), 1, 1, 1); // dummy surface parameters
	Material yellowLightGlass = Material(glm::vec3(1, 1, 0.6), 1, 1, 1); // dummy surface parameters

	ShaderProgram surfaceShaderProgram = ShaderProgram(SH_SURFACE_VERTEX, SH_SURFACE_FRAGMENT);
	ShaderProgram lightShaderProgram = ShaderProgram(SH_LIGHT_VERTEX, SH_LIGHT_FRAGMENT);

	Mesh airportGround = Mesh(surfaceShaderProgram, SM_AIRPORT_GROUND, defaultMaterial, T_GRASS);
	Mesh airportRunway = Mesh(surfaceShaderProgram, SM_AIRPORT_RUNWAY, defaultMaterial, T_ASPHALT);
	Mesh airportApron = Mesh(surfaceShaderProgram, SM_AIRPORT_APRON, defaultMaterial, T_ASPHALT_BRIGHT);
	Mesh airportTower = Mesh(surfaceShaderProgram, SM_AIRPORT_TOWER, concrete, T_CONCRETE);
	Mesh airportHangar = Mesh(surfaceShaderProgram, SM_AIRPORT_HANGAR, defaultMaterial, T_TENT);
	Mesh airportLightBody = Mesh(surfaceShaderProgram, SM_AIRPORT_LIGHT_BODY, metal);
	Mesh airportLight = Mesh(lightShaderProgram, SM_AIRPORT_LIGHT, yellowLightGlass);
	Mesh airplaneCap = Mesh(surfaceShaderProgram, SM_AIRPLANE_CAP, metal);
	Mesh airplanePropeller = Mesh(surfaceShaderProgram, SM_AIRPLANE_PROPELLER, metal);
	Mesh airplaneBody = Mesh(surfaceShaderProgram, SM_AIRPLANE_BODY, defaultMaterial, T_CAMO);
	Mesh airplaneJoins = Mesh(surfaceShaderProgram, SM_AIRPLANE_JOINS, metal);
	Mesh airplaneTires = Mesh(surfaceShaderProgram, SM_AIRPLANE_TIRES, rubber);
	Mesh airplaneLight = Mesh(lightShaderProgram, SM_AIRPLANE_LIGHT, whiteLightGlass);
	Mesh zeppelinBody = Mesh(surfaceShaderProgram, SM_ZEPPELIN_BODY, zeppelinCanvas);

	Airport airport = Airport(surfaceShaderProgram, lightShaderProgram, airportGround, airportRunway,
		airportApron, airportTower, airportHangar, airportLightBody, airportLight);
	std::vector<Airplane> airplanes;
	for(int i = 0; i < airplanesCount; i++) {
		airplanes.push_back(Airplane(surfaceShaderProgram, lightShaderProgram, airplaneCap, airplanePropeller,
			airplaneBody, airplaneJoins, airplaneTires, airplaneLight));
	}
	Zeppelin zeppelin = Zeppelin(surfaceShaderProgram, lightShaderProgram, zeppelinBody);
	DirectionalLightModel moon = DirectionalLightModel(surfaceShaderProgram, lightShaderProgram,
		glm::vec3(0, 0, 0));
	setScene(airplanes, zeppelin, moon);

	ModelCamera airplaneCamera = ModelCamera(60, (float)gWidth/gHeight, 0.01, 1000, airplanes[0]);
	TrackingCamera trackingCamera = TrackingCamera(60, (float)gWidth/gHeight, 0.01, 1000, airplanes[0]);
	PerspectiveCamera stationaryCamera = PerspectiveCamera(100, (float)gWidth/gHeight, 0.01, 1000);
	setCameras(airplaneCamera, trackingCamera, stationaryCamera);
	
	windowPayload.controlledModel = &airplanes[0];
	windowPayload.usedCamera = &airplaneCamera;
	windowPayload.cameras[0] = &airplaneCamera;
	windowPayload.cameras[1] = &trackingCamera;
	windowPayload.cameras[2] = &stationaryCamera;
	
	Time::updateTime();
	DayNightCycle::setMoon(&moon);

	while(!glfwWindowShouldClose(window)) {
		Time::updateTime();
		DayNightCycle::updateTimeOfDay();
		DayNightCycle::updateGlobalShading();
		float deltaTime = Time::getDeltaTime();
		processInput(window);
		airplanes[0].rotatePropeller(propellerAngVelocityDeg*deltaTime);

		GlobalShading::use(surfaceShaderProgram, lightShaderProgram);
		windowPayload.usedCamera->use(surfaceShaderProgram, lightShaderProgram);

		for(int i = 0; i < airplanesCount; i++) {
			airplanes[i].render();
		}
		zeppelin.render();
		airport.render();

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

	gWidth = width;
	gHeight = height;
	WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);
	for(int i = 0; i < 3; i++) {
		windowPayload->cameras[i]->setAspectRatio((float)width/height);
	}
	glViewport(0, 0, width, height);
}

void setScene(std::vector<Airplane>& airplanes, Zeppelin& zeppelin, DirectionalLightModel& moon) {
	airplanes[0].translate(glm::vec3(0, 100, 550));
	airplanes[0].pitch(-15);
	airplanes[1].yaw(45);
	airplanes[1].translate(glm::vec3(-60, 1.75, 30));
	airplanes[1].pitch(12.5);
	airplanes[2].yaw(45);
	airplanes[2].translate(glm::vec3(-60, 1.75, 50));
	airplanes[2].pitch(12.5);
	airplanes[3].yaw(45);
	airplanes[3].translate(glm::vec3(-60, 1.75, 70));
	airplanes[3].pitch(12.5);
	airplanes[4].yaw(90);
	airplanes[4].translate(glm::vec3(-105, 1.75, 125));
	airplanes[4].pitch(12.5);

	zeppelin.translate(glm::vec3(100, 150, -250));

	moon.pitch(-45);
}

void setCameras(ModelCamera& airplaneCamera, TrackingCamera& trackingCamera,
	PerspectiveCamera& stationaryCamera) {
	airplaneCamera.translate(glm::vec3(0, 1, 4));
	airplaneCamera.pitch(-10);

	trackingCamera.translate(glm::vec3(140, 70, 0));

	stationaryCamera.translate(glm::vec3(-150, 100, -150));
	stationaryCamera.yaw(110);
	stationaryCamera.pitch(-30);
}

void processInput(GLFWwindow* window) {
	WindowPayload* windowPayload = (WindowPayload*)glfwGetWindowUserPointer(window);
	float deltaTime = Time::getDeltaTime();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		windowPayload->usedCamera = windowPayload->cameras[0];
	}
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		windowPayload->usedCamera = windowPayload->cameras[1];
	}
	if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		windowPayload->usedCamera = windowPayload->cameras[2];
	}

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		windowPayload->controlledModel->moveForwards(velocity*deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		windowPayload->controlledModel->moveBackwards(velocity*deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		windowPayload->controlledModel->yaw(-angVelocityDeg*deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		windowPayload->controlledModel->yaw(angVelocityDeg*deltaTime);
	}
	
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		windowPayload->controlledModel->pitch(-angVelocityDeg*deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		windowPayload->controlledModel->pitch(angVelocityDeg*deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		windowPayload->controlledModel->roll(-angVelocityDeg*deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		windowPayload->controlledModel->roll(angVelocityDeg*deltaTime);
	}
}

float c2f(unsigned char color) {
	if(color < 0) return 0;
	if(color > 255) return 1;
	return (float)color/255;
}
