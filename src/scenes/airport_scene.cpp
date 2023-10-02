#include "scenes/airport_scene.hpp"

#include "graphics/cameras/camera.hpp"
#include "graphics/cameras/model_camera.hpp"
#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/cameras/tracking_camera.hpp"
#include "graphics/day_night_cycle.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/paths.hpp"
#include "graphics/shader_program.hpp"
#include "models/airplane.hpp"
#include "models/airport.hpp"
#include "models/directional_light_model.hpp"
#include "models/zeppelin.hpp"
#include "physics/airplane_models/airplane_models.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "scenes/scene.hpp"
#include "time.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

constexpr float airplaneVelocity = 50;
constexpr float airplaneAngVelocityDeg = 60;

AirportScene::AirportScene(const ShaderProgram& surfaceShaderProgram,
	const ShaderProgram& lightShaderProgram, float aspectRatio) :
	Scene{surfaceShaderProgram, lightShaderProgram}
{
	createMeshes();
	createModels();
	createCameras(aspectRatio);
	setModels();
	setCameras();
}

void AirportScene::update()
{
	DayNightCycle::update(m_surfaceShaderProgram, m_lightShaderProgram);

	float deltaTime = Time::getDeltaTime();
	constexpr float propellerAngVelocityDeg = 360;
	m_airplanes[0]->rotatePropeller(propellerAngVelocityDeg * deltaTime);
	m_airplanes[0]->update();
}

void AirportScene::render()
{
	m_activeCamera->use(m_surfaceShaderProgram, m_lightShaderProgram);

	for (const std::unique_ptr<Airplane>& airplane : m_airplanes)
	{
		airplane->render();
	}
	m_airport->render();
	m_zeppelin->render();
}

void AirportScene::setAspectRatio(float aspectRatio)
{
	m_airplaneCamera->setAspectRatio(aspectRatio);
	m_trackingCamera->setAspectRatio(aspectRatio);
	m_stationaryCamera->setAspectRatio(aspectRatio);
}

void AirportScene::setActiveCamera(unsigned int cameraId)
{
	switch (cameraId)
	{
	case 1:
		m_activeCamera = m_airplaneCamera.get();
		break;
	case 2:
		m_activeCamera = m_trackingCamera.get();
		break;
	case 3:
		m_activeCamera = m_stationaryCamera.get();
		break;
	}
}

void AirportScene::ctrlPitch(float relative)
{
	m_airplanes[0]->ctrlPitch(relative);
}

void AirportScene::ctrlYaw(float relative)
{
	m_airplanes[0]->ctrlYaw(relative);
}

void AirportScene::ctrlRoll(float relative)
{
	m_airplanes[0]->ctrlRoll(relative);
}

void AirportScene::ctrlThrust(float relative)
{
	m_airplanes[0]->ctrlThrust(relative);
}

void AirportScene::createMeshes()
{
	// dummy color
	const Material defaultMaterial{glm::vec3{1, 0, 0}, 0.75, 0.25, 10};
	// dummy color
	const Material concrete{glm::vec3{1, 0, 0}, 0.75, 0, 10};
	const Material metal{glm::vec3{0.25, 0.25, 0.25}, 0.75, 0.25, 10};
	const Material rubber{glm::vec3{0.1, 0.1, 0.1}, 0.75, 0.25, 10};
	const Material zeppelinCanvas{glm::vec3{0.9, 0.9, 0.9}, 0.75, 0.25, 10};
	// dummy surface params
	const Material whiteLightGlass{glm::vec3{1, 1, 1}, 1, 1, 1};
	// dummy surface params
	const Material yellowLightGlass{glm::vec3{1, 1, 0.6}, 1, 1, 1};
	
	m_airplaneCap = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPLANE_CAP, metal);
	m_airplanePropeller = std::make_unique<const Mesh>(m_surfaceShaderProgram,
		SM_AIRPLANE_PROPELLER, metal);
	m_airplaneBody = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPLANE_BODY,
		defaultMaterial, T_CAMO);
	m_airplaneJoins = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPLANE_JOINS,
		metal);
	m_airplaneTires = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPLANE_TIRES,
		rubber);
	m_airplaneLight = std::make_unique<const Mesh>(m_lightShaderProgram, SM_AIRPLANE_LIGHT,
		whiteLightGlass);
	m_airportGround = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPORT_GROUND,
		defaultMaterial, T_GRASS);
	m_airportRunway = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPORT_RUNWAY,
		defaultMaterial, T_ASPHALT);
	m_airportApron = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPORT_APRON,
		defaultMaterial, T_ASPHALT_BRIGHT);
	m_airportTower = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPORT_TOWER,
		concrete, T_CONCRETE);
	m_airportHangar = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPORT_HANGAR,
		defaultMaterial, T_TENT);
	m_airportLightBody = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_AIRPORT_LIGHT_BODY,
		metal);
	m_airportLight = std::make_unique<const Mesh>(m_lightShaderProgram, SM_AIRPORT_LIGHT,
		yellowLightGlass);
	m_zeppelinBody = std::make_unique<const Mesh>(m_surfaceShaderProgram, SM_ZEPPELIN_BODY,
		zeppelinCanvas);
}

void AirportScene::createModels()
{
	constexpr std::size_t airplanesCount = 5;
	for (std::size_t i = 0; i < airplanesCount; ++i)
	{
		m_airplanes.push_back(std::make_unique<Airplane>(m_surfaceShaderProgram,
			m_lightShaderProgram, *m_airplaneCap, *m_airplanePropeller, *m_airplaneBody,
			*m_airplaneJoins, *m_airplaneTires, *m_airplaneLight, mustang));
	}

	m_airport = std::make_unique<Airport>(m_surfaceShaderProgram, m_lightShaderProgram,
		*m_airportGround, *m_airportRunway, *m_airportApron, *m_airportTower, *m_airportHangar,
		*m_airportLightBody, *m_airportLight);

	m_zeppelin = std::make_unique<Zeppelin>(m_surfaceShaderProgram, m_lightShaderProgram,
		*m_zeppelinBody);

	m_moon = std::make_unique<DirectionalLightModel>(m_surfaceShaderProgram, m_lightShaderProgram,
		glm::vec3{0, 0, 0});
	DayNightCycle::setMoon(*m_moon);
}

void AirportScene::createCameras(float aspectRatio)
{
	constexpr float nearPlane = 0.01f;
	constexpr float farPlane = 1000;
	m_airplaneCamera = std::make_unique<ModelCamera>((float)60, aspectRatio, nearPlane, farPlane,
		*m_airplanes[0]);
	m_trackingCamera = std::make_unique<TrackingCamera>((float)60, aspectRatio, nearPlane, farPlane,
		*m_airplanes[0]);
	m_stationaryCamera = std::make_unique<PerspectiveCamera>((float)100, aspectRatio, nearPlane,
		farPlane);
}

void AirportScene::setModels()
{
	constexpr float moonRotationPitch = -45;
	m_moon->rotatePitch(moonRotationPitch);

	constexpr glm::vec3 zeppelinPosition{100, 150, -250};
	m_zeppelin->translate(zeppelinPosition);

	constexpr glm::vec3 ctrlAirplaneInitPosition{0, 100, 1000};
	m_airplanes[0]->translate(ctrlAirplaneInitPosition);
	m_airplanes[0]->rotatePitch(8);
	State state = m_airplanes[0]->getState();
	constexpr glm::vec3 ctrlAirplaneInitVelocity{0, 0, -100};
	state.velocity = ctrlAirplaneInitVelocity;
	m_airplanes[0]->setState(state);

	constexpr float staticAirplanesPositionY = 1.75f;

	constexpr float apronAirplanesPositionX = -60;
	constexpr float firstApronAirplanePositionZ = 30;
	constexpr float apronAirplanesGapZ = 20;
	constexpr float apronAirplanesRotationYawDeg = 45;
	constexpr float apronAirplanesRotationPitchDeg = 12.5f;
	for(size_t i = 1; i <= 3; i++)
	{
		m_airplanes[i]->translate(glm::vec3{apronAirplanesPositionX, staticAirplanesPositionY,
			firstApronAirplanePositionZ + ((int)i - 1)*apronAirplanesGapZ});
		m_airplanes[i]->rotateYaw(apronAirplanesRotationYawDeg);
		m_airplanes[i]->rotatePitch(apronAirplanesRotationPitchDeg);
	}
	
	constexpr float hangarAirplaneRotationYawDeg = 90;
	constexpr float hangarAirplaneRotationPitchDeg = 12.5f;
	constexpr glm::vec3 hangarAirplanePosition{-105, staticAirplanesPositionY, 125};
	m_airplanes[4]->rotateYaw(hangarAirplaneRotationYawDeg);
	m_airplanes[4]->rotatePitch(hangarAirplaneRotationPitchDeg);
	m_airplanes[4]->translate(hangarAirplanePosition);
}

void AirportScene::setCameras()
{
	constexpr float airplaneCameraPitchDeg = -10;
	constexpr glm::vec3 airplaneCameraPosition{0, 4, 16};
	m_airplaneCamera->rotatePitch(airplaneCameraPitchDeg);
	m_airplaneCamera->translate(airplaneCameraPosition);

	constexpr glm::vec3 trackingCameraPosition{140, 70, 0};
	m_trackingCamera->translate(trackingCameraPosition);
	
	constexpr float stationaryCameraRotationYawDeg = 110;
	constexpr float stationaryCameraRotationPitchDeg = -30;
	constexpr glm::vec3 stationaryCameraPosition{-150, 100, -150};
	m_stationaryCamera->rotateYaw(stationaryCameraRotationYawDeg);
	m_stationaryCamera->rotatePitch(stationaryCameraRotationPitchDeg);
	m_stationaryCamera->translate(stationaryCameraPosition);

	m_activeCamera = m_airplaneCamera.get();
}
