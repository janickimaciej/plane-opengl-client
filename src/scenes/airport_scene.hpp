#ifndef AIRPORT_SCENE
#define AIRPORT_SCENE

#include <vector>
#include "../models/directional_light_model.hpp"
#include "../models/airport.hpp"
#include "../models/zeppelin.hpp"
#include "../models/airplane.hpp"
#include "../cameras/model_camera.hpp"
#include "../cameras/tracking_camera.hpp"
#include "../cameras/perspective_camera.hpp"

class AirportScene {
	const ShaderProgram& surfaceShaderProgram;
	const ShaderProgram& lightShaderProgram;

	Mesh* airportGround;
	Mesh* airportRunway;
	Mesh* airportApron;
	Mesh* airportTower;
	Mesh* airportHangar;
	Mesh* airportLightBody;
	Mesh* airportLight;
	Mesh* airplaneCap;
	Mesh* airplanePropeller;
	Mesh* airplaneBody;
	Mesh* airplaneJoins;
	Mesh* airplaneTires;
	Mesh* airplaneLight;
	Mesh* zeppelinBody;

	DirectionalLightModel* moon;
	Airport* airport;
	Zeppelin* zeppelin;
	std::vector<Airplane> airplanes;

	ModelCamera* airplaneCamera;
	TrackingCamera* trackingCamera;
	PerspectiveCamera* stationaryCamera;

	Camera* activeCamera;

	void createMeshes();
	void createModels();
	void createCameras(float aspectRatio);
	void setModels();
	void setCameras();
public:
	AirportScene(const ShaderProgram& surfaceShaderProgram,
		const ShaderProgram& lightShaderProgram, float aspectRatio);
	void update();
	void render();
	void setAspectRatio(float aspectRatio);
	void setActiveCamera(unsigned int cameraId);

	void controlForwards();
	void controlBackwards();
	void controlYawNegative();
	void controlYawPositive();
	void controlPitchNegative();
	void controlPitchPositive();
	void controlRollNegative();
	void controlRollPositive();

	~AirportScene();
};

#endif
