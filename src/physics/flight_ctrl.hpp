#ifndef FLIGHT_CTRL_HPP
#define FLIGHT_CTRL_HPP

//#include "graphics/mesh_instance.hpp"
#include "physics/airplane_params/airplane_params.hpp"

class FlightCtrl
{
public:
	FlightCtrl(/*MeshInstance& elevator, MeshInstance& rudder, MeshInstance& leftAileron,
		MeshInstance& rightAileron, */const AirplaneParams& airplaneParams);
	float getElevatorAngleRad() const;
	void ctrlPitch(float relative);
	float getRudderAngleRad() const;
	void ctrlYaw(float relative);
	float getAileronsAngleRad() const;
	void ctrlRoll(float relative);
	float getThrustRelative() const;
	void ctrlThrust(float relative);
	
private:
	//MeshInstance& m_elevator;
	//MeshInstance& m_rudder;
	//MeshInstance& m_leftAileron;
	//MeshInstance& m_rightAileron;

	const AirplaneParams& m_airplaneParams;
	float m_elevatorAngleRad{};
	float m_rudderAngleRad{};
	float m_aileronsAngleRad{};
	float m_thrustRelative{};

	// converts linearly from [-1, 1] to [min, max]
	float relativeToAbs(float relative, float min, float max) const;
};

#endif
