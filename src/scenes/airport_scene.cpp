#include "airport_scene.hpp"
#include "../paths.hpp"
#include "../day_night_cycle.hpp"
#include "../time.hpp"

constexpr int airplanesCount = 5;
constexpr float velocity = 50;
constexpr float angVelocityDeg = 60;
constexpr float propellerAngVelocityDeg = 360;

void AirportScene::createMeshes() {
	Material defaultMaterial = Material(glm::vec3(1, 0, 0), 0.75, 0.25, 10); // dummy color
	Material concrete = Material(glm::vec3(1, 0, 0), 0.75, 0, 10); // dummy color
	Material metal = Material(glm::vec3(0.25, 0.25, 0.25), 0.75, 0.25, 10);
	Material rubber = Material(glm::vec3(0.1, 0.1, 0.1), 0.75, 0.25, 10);
	Material zeppelinCanvas = Material(glm::vec3(0.9, 0.9, 0.9), 0.75, 0.25, 10);
	Material whiteLightGlass = Material(glm::vec3(1, 1, 1), 1, 1, 1); // dummy surface parameters
	Material yellowLightGlass = Material(glm::vec3(1, 1, 0.6), 1, 1, 1); // dummy surface parameters

	airportGround = new Mesh(surfaceShaderProgram, SM_AIRPORT_GROUND, defaultMaterial, T_GRASS);
	airportRunway = new Mesh(surfaceShaderProgram, SM_AIRPORT_RUNWAY, defaultMaterial, T_ASPHALT);
	airportApron = new Mesh(surfaceShaderProgram, SM_AIRPORT_APRON, defaultMaterial, T_ASPHALT_BRIGHT);
	airportTower = new Mesh(surfaceShaderProgram, SM_AIRPORT_TOWER, concrete, T_CONCRETE);
	airportHangar = new Mesh(surfaceShaderProgram, SM_AIRPORT_HANGAR, defaultMaterial, T_TENT);
	airportLightBody = new Mesh(surfaceShaderProgram, SM_AIRPORT_LIGHT_BODY, metal);
	airportLight = new Mesh(lightShaderProgram, SM_AIRPORT_LIGHT, yellowLightGlass);
	airplaneCap = new Mesh(surfaceShaderProgram, SM_AIRPLANE_CAP, metal);
	airplanePropeller = new Mesh(surfaceShaderProgram, SM_AIRPLANE_PROPELLER, metal);
	airplaneBody = new Mesh(surfaceShaderProgram, SM_AIRPLANE_BODY, defaultMaterial, T_CAMO);
	airplaneJoins = new Mesh(surfaceShaderProgram, SM_AIRPLANE_JOINS, metal);
	airplaneTires = new Mesh(surfaceShaderProgram, SM_AIRPLANE_TIRES, rubber);
	airplaneLight = new Mesh(lightShaderProgram, SM_AIRPLANE_LIGHT, whiteLightGlass);
	zeppelinBody = new Mesh(surfaceShaderProgram, SM_ZEPPELIN_BODY, zeppelinCanvas);
}

void AirportScene::createModels() {
	airport = new Airport(surfaceShaderProgram, lightShaderProgram, *airportGround, *airportRunway,
		*airportApron, *airportTower, *airportHangar, *airportLightBody, *airportLight);

	zeppelin = new Zeppelin(surfaceShaderProgram, lightShaderProgram, *zeppelinBody);

	for(int i = 0; i < airplanesCount; i++) {
		airplanes.push_back(Airplane(surfaceShaderProgram, lightShaderProgram, *airplaneCap,
			*airplanePropeller, *airplaneBody, *airplaneJoins, *airplaneTires, *airplaneLight));
	}

	moon = new DirectionalLightModel(surfaceShaderProgram, lightShaderProgram,
		glm::vec3(0, 0, 0));
	DayNightCycle::setMoon(moon);
}

void AirportScene::createCameras(float aspectRatio) {
	airplaneCamera = new ModelCamera(60, aspectRatio, 0.01f, 1000, airplanes[0]);
	trackingCamera = new TrackingCamera(60, aspectRatio, 0.01f, 1000, airplanes[0]);
	stationaryCamera = new PerspectiveCamera(100, aspectRatio, 0.01f, 1000);
}

void AirportScene::setModels() {
	moon->pitch(-45);

	zeppelin->translate(glm::vec3(100, 150, -250));

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
}

void AirportScene::setCameras() {
	airplaneCamera->translate(glm::vec3(0, 4, 16));
	airplaneCamera->pitch(-10);

	trackingCamera->translate(glm::vec3(140, 70, 0));

	stationaryCamera->translate(glm::vec3(-150, 100, -150));
	stationaryCamera->yaw(110);
	stationaryCamera->pitch(-30);

	activeCamera = airplaneCamera;
}

AirportScene::AirportScene(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, float aspectRatio) :
	surfaceShaderProgram(surfaceShaderProgram), lightShaderProgram(lightShaderProgram) {
	createMeshes();
	createModels();
	createCameras(aspectRatio);
	setModels();
	setCameras();
}

void AirportScene::update() {
	DayNightCycle::updateTimeOfDay();
	DayNightCycle::updateGlobalShading();
	GlobalShading::use(surfaceShaderProgram, lightShaderProgram);

	float deltaTime = Time::getDeltaTime();
	airplanes[0].rotatePropeller(propellerAngVelocityDeg*deltaTime);
}

void AirportScene::render() {
	activeCamera->use(surfaceShaderProgram, lightShaderProgram);

	for(int i = 0; i < airplanesCount; i++) {
		airplanes[i].render();
	}
	zeppelin->render();
	airport->render();
}

void AirportScene::setAspectRatio(float aspectRatio) {
	airplaneCamera->setAspectRatio(aspectRatio);
	trackingCamera->setAspectRatio(aspectRatio);
	stationaryCamera->setAspectRatio(aspectRatio);
}

void AirportScene::setActiveCamera(unsigned int cameraId) {
	switch(cameraId) {
	case 1:
		activeCamera = airplaneCamera;
		break;
	case 2:
		activeCamera = trackingCamera;
		break;
	case 3:
		activeCamera = stationaryCamera;
		break;
	}
}

void AirportScene::ctrlMoveAlongZNegative() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].moveAlongZ(-velocity*deltaTime);
}

void AirportScene::ctrlMoveAlongZPositive() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].moveAlongZ(velocity*deltaTime);
}

void AirportScene::ctrlYawNegative() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].yaw(-angVelocityDeg*deltaTime);
}

void AirportScene::ctrlYawPositive() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].yaw(angVelocityDeg*deltaTime);
}

void AirportScene::ctrlPitchNegative() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].pitch(-angVelocityDeg*deltaTime);
}

void AirportScene::ctrlPitchPositive() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].pitch(angVelocityDeg*deltaTime);
}

void AirportScene::ctrlRollNegative() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].roll(-angVelocityDeg*deltaTime);
}

void AirportScene::ctrlRollPositive() {
	float deltaTime = Time::getDeltaTime();
	airplanes[0].roll(angVelocityDeg*deltaTime);
}

AirportScene::~AirportScene() {
	delete airportGround;
	delete airportRunway;
	delete airportApron;
	delete airportTower;
	delete airportHangar;
	delete airportLightBody;
	delete airportLight;
	delete airplaneCap;
	delete airplanePropeller;
	delete airplaneBody;
	delete airplaneJoins;
	delete airplaneTires;
	delete airplaneLight;
	delete zeppelinBody;

	delete moon;
	delete airport;
	delete zeppelin;

	delete airplaneCamera;
	delete trackingCamera;
	delete stationaryCamera;
}
