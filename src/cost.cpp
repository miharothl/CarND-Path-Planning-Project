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

  auto cur_state = vehicle->machine_->GetCurrentState();

  std::cout << typeid(*cur_state).name();
  std::cout << " --> cost: " << cost << std::endl;

 return cost;
}

double Cost::ChangeLaneCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

  int current = vehicle->GetLane();
  int proposed = vehicle->GetProposedLane();

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
  int proposed = vehicle->GetProposedLane();

  double cost = 0.;

  vector<Measurement> filtered_by_lane;

  Road road;

  for (auto m : trafic_measurement) {
    if (proposed == road.GetLane(m.D()))
    {
      filtered_by_lane.push_back(m);
    }
  }

  bool colision = false;

  for (auto f : filtered_by_lane)
  {
    auto ego_s = vehicle->current_measurement_->S();

    if ((f.S() > ego_s) && (f.S() - ego_s < 30))
    {
      colision = true;
    }
  }

  if (colision) {
    auto time_til_collision = 1;
    auto exponent = pow(float(time_til_collision), 2);
    auto mult = exp(-exponent);

     cost =  mult * this->kCollision;
  }

  return cost;
}
