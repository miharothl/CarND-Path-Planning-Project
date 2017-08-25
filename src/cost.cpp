//
// Created by Miha Röthl on 17/08/2017.
//

#include "cost.h"

#include <vector>
#include <iostream>
#include "state/states/state.h"

#include "measurement.h"

using namespace std;

double Cost::CalculateCost(Vehicle *vehicle) {

  double cost = 0.;

  cost += ChangeLaneCost(vehicle, vehicle->meassurements_);
  cost += ColisionCost(vehicle, vehicle->meassurements_);
  cost += this->CouldGoFaster(vehicle, vehicle->meassurements_);

  auto cur_state = vehicle->machine_->GetCurrentState();

  std::cout << typeid(*cur_state).name();
  std::cout << " --> cost: " << cost << std::endl;

 return cost;
}

double Cost::ChangeLaneCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

  int current = vehicle->GetLane();
  int proposed = vehicle->GetTargetLane();

  Road road;

  double cost = 0.;

  if (proposed != current)
  {
    cost += this->kComfort;
  }

  if (!road.IsLaneAllowed(proposed))
  {
    cost += this->kCollision;
  }

  return cost;
}

double Cost::ColisionCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

  int current = vehicle->GetLane();
  int proposed = vehicle->GetTargetLane();

  double cost = 0.;

  vector<Measurement> filtered_by_lane;

  Road road;

  for (auto m : trafic_measurement) {
    if (proposed == road.GetLane(m.D()))
    {
      filtered_by_lane.push_back(m);
    }
  }

  bool collision = false;

  for (auto f : filtered_by_lane)
  {
    auto ego_s = vehicle->current_measurement_->S();

    if ( (f.S()>(ego_s-5)) && (f.S()-ego_s< 30) )
    {
      if (vehicle->GetTargetSpeed() > f.V())
      {
        collision = true;
      }

//      auto ego = vehicle->GetTargetSpeed();
//      auto traffic = f.V();
//
//      cost = cost + vehicle->machine_->GetCurrentState()->CostForState(ego, traffic);
    }
  }

   auto ego = vehicle->GetTargetSpeed();
   auto traffic = road.GetSpeedLimitForLane(vehicle->GetTargetLane());

   cost = cost + vehicle->machine_->GetCurrentState()->CostForState(ego, traffic);

  cost = cost + vehicle->machine_->GetCurrentState()->CostForState();

  if (collision) {
    auto time_til_collision = 1;
    auto exponent = pow(float(time_til_collision), 2);
    auto mult = exp(-exponent);

     cost =  mult * this->kCollision;
  }

  return cost;
}

double Cost::CouldGoFaster(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

  double cost;
  cost = 0;

  if (vehicle->GetTargetLane() - vehicle->GetLane() < 0)
  {
    cost = -10025;
  }

//  if (vehicle->machine_->GetCurrentState()->IsChaingingLanes()) {
//    if (vehicle->current_measurement_->V() < vehicle->GetTargetSpeed()) {
//      cost = cost - 10000;
//      cout << "Could Go Faster" << endl;
//    }
//  }
  return cost;
}



