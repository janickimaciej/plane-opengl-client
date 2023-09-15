#ifndef AIRPLANE_DYNAMICS_HPP
#define AIRPLANE_DYNAMICS_HPP

#include "flight_ctrl.hpp"
#include "model_dynamics/rigid_body_dynamics.hpp"
#include "structs/airplane_params.hpp"
#include "structs/state.hpp"

#include <glm/glm.hpp>

class AirplaneDynamics : public RigidBodyDynamics
{
public:
	AirplaneDynamics(const AirplaneParams& params, const FlightCtrl& flightCtrl);
	virtual ~AirplaneDynamics() = default;

private:
	const AirplaneParams m_params;
	const FlightCtrl& m_flightCtrl;

	virtual void computeNetForceAndNetTorque(const State& state, glm::vec3& netForce,
		glm::vec3& netTorque) const override;
};

#endif
