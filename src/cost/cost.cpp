//
// Created by Miha Röthl on 17/08/2017.
//

#include "cost.h"

double Cost::CalculateCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

  double cost = 0.;

  cost += ChangeLaneCost(vehicle, trafic_measurement);

 return cost;
}

double Cost::ChangeLaneCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement) {

  int current = vehicle->GetLane();
  int proposed = vehicle->GetProposedLane();

  double cost = 0.;

  if (proposed != current)
  {
    cost =+ this->kComfort;
  }

  return cost;
}

