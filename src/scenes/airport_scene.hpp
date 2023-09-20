#ifndef AIRPORT_SCENE_HPP
#define AIRPORT_SCENE_HPP

#include "graphics/cameras/model_camera.hpp"
#include "graphics/cameras/perspective_camera.hpp"
#include "graphics/cameras/tracking_camera.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"
#include "models/airplane.hpp"
#include "models/airport.hpp"
#include "models/directional_light_model.hpp"
#include "models/zeppelin.hpp"
#include "scenes/scene.hpp"

#include <vector>

class AirportScene : public Scene
{
public:
	AirportScene(const ShaderProgram& surfaceShaderProgram, const ShaderProgram& lightShaderProgram,
		float aspectRatio);

	virtual void update() override;
	virtual void render() override;
	virtual void setAspectRatio(float aspectRatio) override;
	virtual void setActiveCamera(unsigned int cameraId) override;
	
	virtual void ctrlPitch(float relative) override;
	virtual void ctrlYaw(float relative) override;
	virtual void ctrlRoll(float relative) override;
	virtual void ctrlThrust(float relative) override;

	~AirportScene();

private:
	const Mesh* m_airportGround{};
	const Mesh* m_airportRunway{};
	const Mesh* m_airportApron{};
	const Mesh* m_airportTower{};
	const Mesh* m_airportHangar{};
	const Mesh* m_airportLightBody{};
	const Mesh* m_airportLight{};
	const Mesh* m_airplaneCap{};
	const Mesh* m_airplanePropeller{};
	const Mesh* m_airplaneBody{};
	const Mesh* m_airplaneJoins{};
	const Mesh* m_airplaneTires{};
	const Mesh* m_airplaneLight{};
	const Mesh* m_zeppelinBody{};

	DirectionalLightModel* m_moon{};
	Airport* m_airport{};
	Zeppelin* m_zeppelin{};
	std::vector<Airplane> m_airplanes{};

	ModelCamera* m_airplaneCamera{};
	TrackingCamera* m_trackingCamera{};
	PerspectiveCamera* m_stationaryCamera{};

	void createMeshes();
	void createModels();
	void createCameras(float aspectRatio);
	void setModels();
	void setCameras();
};

#endif
