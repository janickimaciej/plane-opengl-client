#ifndef WINDOW_PAYLOAD
#define WINDOW_PAYLOAD

#include "../cameras/perspective_camera.hpp"
#include "../models/airplane.hpp"
#include "../scenes/airport_scene.hpp"

struct WindowPayload {
	AirportScene* airportScene;
};

#endif
