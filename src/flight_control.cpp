#include "flight_control.hpp"

FlightControl::FlightControl(/*MeshInstance& elevator, MeshInstance& rudder, MeshInstance& leftAileron,
	MeshInstance& rightAileron, */ControlSurfacesConstraints controlSurfacesConstraints) :
	/*elevator(elevator), rudder(rudder), leftAileron(leftAileron), rightAileron(rightAileron),*/
	controlSurfacesConstraints(controlSurfacesConstraints) {
	setElevatorAngleRelative(0);
	setRudderAngleRelative(0);
	setAileronsAngleRelative(0);
	setThrustRelative(0);
}

float FlightControl::getElevatorAngleDeg() const {
	return elevatorAngleDeg;
}

void FlightControl::setElevatorAngleRelative(float angleRelative) {
	float newElevatorAngleDeg = controlSurfacesConstraints.elevatorMinAngleDeg +
		(controlSurfacesConstraints.elevatorMaxAngleDeg -
		controlSurfacesConstraints.elevatorMinAngleDeg)*angleRelative;
	//TODO: rotate mesh
	elevatorAngleDeg = newElevatorAngleDeg;
}

float FlightControl::getRudderAngleDeg() const {
	return rudderAngleDeg;
}

void FlightControl::setRudderAngleRelative(float angleRelative) {
	float newRudderAngleDeg = controlSurfacesConstraints.rudderMinAngleDeg +
		(controlSurfacesConstraints.rudderMaxAngleDeg -
		controlSurfacesConstraints.rudderMinAngleDeg)*angleRelative;
	//TODO: rotate mesh
	rudderAngleDeg = newRudderAngleDeg;
}

float FlightControl::getAileronsAngleDeg() const {
	return aileronsAngleDeg;
}

void FlightControl::setAileronsAngleRelative(float angleRelative) {
	float newAileronsAngleDeg = controlSurfacesConstraints.aileronsMinMaxAngleDeg +
		2*controlSurfacesConstraints.aileronsMinMaxAngleDeg*angleRelative;
	//TODO: rotate mesh
	aileronsAngleDeg = newAileronsAngleDeg;
}

float FlightControl::getThrustRelative() const {
	return thrustRelative;
}

void FlightControl::setThrustRelative(float relative) {
	thrustRelative = relative;
}
