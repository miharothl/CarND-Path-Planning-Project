//
// Created by Miha Röthl on 22/08/2017.
//



#include "following_state.h"

#include <vector>
#include <cmath>

#include "../../vehicle.h"

using namespace std;

FollowingState::FollowingState(Controller *controller) {
  this->controller_ = controller;
}

FollowingState::~FollowingState() {

}

double FollowingState::GetTargetSpeed(Vehicle *vehicle) {

  int proposedLane = vehicle->GetTargetLane();

  vector<Measurement> filtered_by_lane;

  Road road;

  for (auto m : vehicle->meassurements_) {
    if (proposedLane == road.GetLane(m.D()))
    {
      filtered_by_lane.push_back(m);
    }
  }

  bool collision = false;
  double collisionVehicleSpeed;

  for (auto f : filtered_by_lane)
  {
    auto ego_s = vehicle->current_measurement_->S();

    if ((f.S() > ego_s) && (f.S() - ego_s < 30))
    {
      collision = true;
      collisionVehicleSpeed = f.V();
    }
  }

  if (collision == true){
    return collisionVehicleSpeed;
  } else {
    return State::GetTargetSpeed(vehicle);
  }
}

double FollowingState::CostForState() {
  return 10050;
}

double FollowingState::CostForState(double ego_speed, double traffic_speed) {

  if (fabs(ego_speed - traffic_speed) < 2.)
  {
    return -500;
  }
  return 0.;
}
