#ifndef AIRPORT_SCENE
#define AIRPORT_SCENE

#include <vector>
#include "scene.hpp"
#include "../models/directional_light_model.hpp"
#include "../models/airport.hpp"
#include "../models/zeppelin.hpp"
#include "../models/airplane.hpp"
#include "../cameras/model_camera.hpp"
#include "../cameras/tracking_camera.hpp"
#include "../cameras/perspective_camera.hpp"

class AirportScene : public Scene {
	const Mesh* airportGround;
	const Mesh* airportRunway;
	const Mesh* airportApron;
	const Mesh* airportTower;
	const Mesh* airportHangar;
	const Mesh* airportLightBody;
	const Mesh* airportLight;
	const Mesh* airplaneCap;
	const Mesh* airplanePropeller;
	const Mesh* airplaneBody;
	const Mesh* airplaneJoins;
	const Mesh* airplaneTires;
	const Mesh* airplaneLight;
	const Mesh* zeppelinBody;

	DirectionalLightModel* moon;
	Airport* airport;
	Zeppelin* zeppelin;
	std::vector<Airplane> airplanes;

	ModelCamera* airplaneCamera;
	TrackingCamera* trackingCamera;
	PerspectiveCamera* stationaryCamera;

	void createMeshes();
	void createModels();
	void createCameras(float aspectRatio);
	void setModels();
	void setCameras();
public:
	AirportScene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		float aspectRatio);
	virtual void update() override;
	virtual void render() override;
	virtual void setAspectRatio(float aspectRatio) override;
	virtual void setActiveCamera(unsigned int cameraId) override;
	
	virtual void ctrlMoveAlongZNegative() override;
	virtual void ctrlMoveAlongZPositive() override;
	virtual void ctrlYawNegative() override;
	virtual void ctrlYawPositive() override;
	virtual void ctrlPitchNegative() override;
	virtual void ctrlPitchPositive() override;
	virtual void ctrlRollNegative() override;
	virtual void ctrlRollPositive() override;

	~AirportScene();
};

#endif
