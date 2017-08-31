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

  cost += ChangeLaneCost(vehicle, vehicle->traffic_data_);
  cost += CollisionCost(vehicle, vehicle->traffic_data_);
  cost += this->DrivingTowardsLeftSideCost(vehicle, vehicle->traffic_data_);

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

  if (!road.IsLaneOnTheRoad(proposed))
  {
    cost += this->kCollision;
  }

  return cost;
}

double Cost::CollisionCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

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
    auto ego_s = vehicle->ego_data_->S();

    auto distance = f.S() - ego_s;

    // traffic ahead
    if ( (distance >= 0) &&
         (distance < 40) )
    {
      vehicle->machine_->GetCurrentState()->LogTrafficAhead(vehicle, distance);

      if (vehicle->GetTargetSpeed() > f.V())
      {
        collision = true;
      }
    }

    // traffic behind
    if ( (distance < 0) &&
         (distance > -20) )
    {
      vehicle->machine_->GetCurrentState()->LogTrafficBehind(vehicle, distance);
//      if (vehicle->GetTargetSpeed()  < f.V())
//      {
        collision = true;
//      }
    }
  }

  auto ego = vehicle->GetTargetSpeed();
  auto traffic = road.GetPreferredSpeedForLane(vehicle->GetTargetLane());

  // If
  cost = cost + vehicle->machine_->GetCurrentState()->CostForState(ego, traffic);

  cost = cost + vehicle->machine_->GetCurrentState()->CostForState();

  if (collision)
  {
    auto time_til_collision = 1;
    auto exponent = pow(float(time_til_collision), 2);
    auto mult = exp(-exponent);

    cost =  mult * this->kCollision;
  }

  return cost;
}

double Cost::DrivingTowardsLeftSideCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {
  double cost;
  cost = 0;

  if (vehicle->GetTargetLane() - vehicle->GetLane() < 0) {
    cost = -10025;
  }

  return cost;
}
