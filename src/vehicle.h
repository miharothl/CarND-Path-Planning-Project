//
// Created by Miha Röthl on 17/08/2017.
//

#ifndef PATH_PLANNING_VEHICLE_H
#define PATH_PLANNING_VEHICLE_H

#include <vector>

#include "measurement.h"
#include "state/machine.h"
#include "road.h"

class Vehicle {

public:
  Measurement *current_measurement_;
  std::vector<Measurement> meassurements_;

//private:
  Machine *machine_;

  Road *road_;

public:
  Vehicle(Machine* machine);

  int GetLane();

  int GetTargetLane();

  double GetTargetSpeed();

  void UpdateEgoData(Measurement *measurement);

  void UpdateTrafficData(std::vector<Measurement> measurements);

  void PlanPath();
};

#endif //PATH_PLANNING_VEHICLE_H
