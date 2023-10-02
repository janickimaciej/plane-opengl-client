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

#include <memory>
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

	virtual ~AirportScene() = default;

private:
	std::unique_ptr<const Mesh> m_airportGround{};
	std::unique_ptr<const Mesh> m_airportRunway{};
	std::unique_ptr<const Mesh> m_airportApron{};
	std::unique_ptr<const Mesh> m_airportTower{};
	std::unique_ptr<const Mesh> m_airportHangar{};
	std::unique_ptr<const Mesh> m_airportLightBody{};
	std::unique_ptr<const Mesh> m_airportLight{};
	std::unique_ptr<const Mesh> m_airplaneCap{};
	std::unique_ptr<const Mesh> m_airplanePropeller{};
	std::unique_ptr<const Mesh> m_airplaneBody{};
	std::unique_ptr<const Mesh> m_airplaneJoins{};
	std::unique_ptr<const Mesh> m_airplaneTires{};
	std::unique_ptr<const Mesh> m_airplaneLight{};
	std::unique_ptr<const Mesh> m_zeppelinBody{};
	
	std::vector<std::unique_ptr<Airplane>> m_airplanes{};
	std::unique_ptr<Airport> m_airport{};
	std::unique_ptr<Zeppelin> m_zeppelin{};
	std::unique_ptr<DirectionalLightModel> m_moon{};

	std::unique_ptr<ModelCamera> m_airplaneCamera{};
	std::unique_ptr<TrackingCamera> m_trackingCamera{};
	std::unique_ptr<PerspectiveCamera> m_stationaryCamera{};

	void createMeshes();
	void createModels();
	void createCameras(float aspectRatio);
	void setModels();
	void setCameras();
};

#endif
