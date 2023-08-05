#ifndef AIRPLANE_DYNAMICS_HPP
#define AIRPLANE_DYNAMICS_HPP

#include "flight_control.hpp"
#include "model_dynamics/rigid_body_dynamics.hpp"
#include "structs/airplane_parameters.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

class AirplaneDynamics : public RigidBodyDynamics
{
public:
	AirplaneDynamics(const AirplaneParameters& parameters, const FlightControl& flightControl);
	virtual ~AirplaneDynamics() = default;

private:
	const AirplaneParameters m_parameters;
	const FlightControl& m_flightControl;

	virtual void computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
		glm::vec3& netTorque) const override;
};

#endif
