#ifndef FLIGHT_CTRL_HPP
#define FLIGHT_CTRL_HPP

//#include "graphics/mesh_instance.hpp"
#include "physics/airplane_params.hpp"

class FlightCtrl
{
public:
	FlightCtrl(/*MeshInstance& elevator, MeshInstance& rudder, MeshInstance& leftAileron,
		MeshInstance& rightAileron, */const AirplaneParams& airplaneParams);
	float getElevatorAngleDeg() const;
	void setElevatorAngleRelative(float angleRelative);
	float getRudderAngleDeg() const;
	void setRudderAngleRelative(float angleRelative);
	float getAileronsAngleDeg() const;
	void setAileronsAngleRelative(float angleRelative);
	float getThrustRelative() const;
	void setThrustRelative(float relative);
	
private:
	//MeshInstance& m_elevator;
	//MeshInstance& m_rudder;
	//MeshInstance& m_leftAileron;
	//MeshInstance& m_rightAileron;

	const AirplaneParams m_airplaneParams;
	float m_elevatorAngleDeg{};
	float m_rudderAngleDeg{};
	float m_aileronsAngleDeg{};
	float m_thrustRelative{};

	// converts linearly from [-1, 1] to [min, max]
	float relativeToAbs(float relative, float min, float max) const;
};

#endif
