#include "flight_ctrl.hpp"

//#include "graphics/mesh_instance.hpp"
#include "physics/airplane_params/airplane_params.hpp"
#include "physics/airplane_params/surface_params.hpp"

FlightCtrl::FlightCtrl(/*MeshInstance& elevator, MeshInstance& rudder,
	MeshInstance& leftAileron, MeshInstance& rightAileron,
	*/const AirplaneParams& airplaneParams) :
	/*m_elevator{elevator},
	m_rudder{rudder},
	m_leftAileron{leftAileron},
	m_rightAileron{rightAileron},*/
	m_airplaneParams{airplaneParams}
{
	ctrlPitch(0);
	ctrlYaw(0);
	ctrlRoll(0);
	ctrlThrust(0);
}

float FlightCtrl::getElevatorAngleRad() const
{
	return m_elevatorAngleRad;
}

void FlightCtrl::ctrlPitch(float relative)
{
	m_elevatorAngleRad = relativeToAbs(relative, m_airplaneParams.hStab.ctrlMinAngleRad,
		m_airplaneParams.hStab.ctrlMaxAngleRad);
	//m_elevator.resetRotation();
	//m_elevator.pitch(-m_elevatorAngleRad);
}

float FlightCtrl::getRudderAngleRad() const
{
	return m_rudderAngleRad;
}

void FlightCtrl::ctrlYaw(float relative)
{
	m_rudderAngleRad = relativeToAbs(relative, m_airplaneParams.vStab.ctrlMinAngleRad,
		m_airplaneParams.vStab.ctrlMaxAngleRad);
	//m_rudder.resetRotation();
	//m_rudder.yaw(m_rudderAngleRad);
}

float FlightCtrl::getAileronsAngleRad() const
{
	return m_aileronsAngleRad;
}

void FlightCtrl::ctrlRoll(float relative)
{
	m_aileronsAngleRad = relativeToAbs(relative, m_airplaneParams.rightWing.ctrlMinAngleRad,
		m_airplaneParams.rightWing.ctrlMaxAngleRad);
	//m_leftAileron.resetRotation();
	//m_leftAileron.pitch(aileronsAngleRad);
	//m_rightAileron.resetRotation();
	//m_rightAileron.pitch(-m_aileronsAngleRad);
}

float FlightCtrl::getThrustRelative() const
{
	return m_thrustRelative;
}

void FlightCtrl::ctrlThrust(float relative)
{
	m_thrustRelative = relative;
}

float FlightCtrl::relativeToAbs(float relative, float min, float max) const
{
	return (min + max + relative * (max - min)) / 2;
}
