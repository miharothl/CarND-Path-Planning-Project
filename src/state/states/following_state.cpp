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

  for (auto m : vehicle->traffic_data_) {
    if (proposedLane == road.GetLane(m.D()))
    {
      filtered_by_lane.push_back(m);
    }
  }

  bool collision = false;
  double collisionVehicleSpeed;

  for (auto f : filtered_by_lane)
  {
    auto ego_s = vehicle->ego_data_->S();

    if ((f.S() > ego_s) && (f.S() - ego_s < 40))
    {
      collision = true;

      if (f.S() - ego_s < 30)
      {
        collisionVehicleSpeed = f.V() - 1;
      } else {
        collisionVehicleSpeed = f.V();
      }
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

double FollowingState::CostForState(double ego_speed, double speed_limit) {

  // if very close to speed limit, follow as it will be hard to overtake
  if (fabs(ego_speed - speed_limit) < 2.)
  {
    return -500;
  }
  return 0.;
}
