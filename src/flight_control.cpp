#include "flight_control.hpp"

FlightControl::FlightControl(/*MeshInstance& elevator, MeshInstance& rudder, MeshInstance& leftAileron,
	MeshInstance& rightAileron, */const ControlSurfacesConstraints& controlSurfacesConstraints) :
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
	elevatorAngleDeg = (controlSurfacesConstraints.elevatorMinAngleDeg + controlSurfacesConstraints.elevatorMaxAngleDeg +
		angleRelative*(controlSurfacesConstraints.elevatorMaxAngleDeg - controlSurfacesConstraints.elevatorMinAngleDeg))/2;
	//elevator.resetRotation();
	//elevator.pitch(-elevatorAngleDeg);
}

float FlightControl::getRudderAngleDeg() const {
	return rudderAngleDeg;
}

void FlightControl::setRudderAngleRelative(float angleRelative) {
	rudderAngleDeg = angleRelative*controlSurfacesConstraints.rudderMaxAngleDeg;
	//rudder.resetRotation();
	//rudder.yaw(rudderAngleDeg);
}

float FlightControl::getAileronsAngleDeg() const {
	return aileronsAngleDeg;
}

void FlightControl::setAileronsAngleRelative(float angleRelative) {
	aileronsAngleDeg = angleRelative*controlSurfacesConstraints.aileronsMaxAngleDeg;
	//leftAileron.resetRotation();
	//leftAileron.pitch(aileronsAngleDeg);
	//rightAileron.resetRotation();
	//rightAileron.pitch(-aileronsAngleDeg);
}

float FlightControl::getThrustRelative() const {
	return thrustRelative;
}

void FlightControl::setThrustRelative(float relative) {
	thrustRelative = relative;
}
