//
// Created by Miha Röthl on 17/08/2017.
//

#ifndef PATH_PLANNING_COST_H
#define PATH_PLANNING_COST_H

#include <cmath>
#include <vector>

#include "vehicle.h"

class Cost {

public:
  // priority levels for costs
  const double kCollision  = pow(10, 6);
  const double kDanger     = pow(10, 5);
  const double kReachGoal  = pow(10, 5);
  const double kComfort    = pow(10, 4);
  const double kEfficiency = pow(10, 2);

public:
  double CalculateCost(Vehicle *vehicle);

  double ChangeLaneCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement);

  double ColisionCost(Vehicle *vehicle, std::vector<Measurement> trafic_measurement);
};


#endif //PATH_PLANNING_COST_H
