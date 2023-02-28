#ifndef WINDOW_PAYLOAD
#define WINDOW_PAYLOAD

#include "../cameras/perspective_camera.hpp"
#include "../models/airplane.hpp"

struct WindowPayload {
	PerspectiveCamera* cameras[3];
	PerspectiveCamera* usedCamera;
	Airplane* controlledModel;
};

#endif
