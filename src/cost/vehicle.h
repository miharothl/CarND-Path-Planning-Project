//
// Created by Miha Röthl on 17/08/2017.
//

#ifndef PATH_PLANNING_VEHICLE_H
#define PATH_PLANNING_VEHICLE_H

#include "../sensor/measurement.h"
#include "../state/machine.h"

class Vehicle {

  Measurement *current_measurement_;

  Machine *machine_;

public:
  Vehicle(Machine* machine);

  int GetLane();

  int GetProposedLane();

  void UpdateCurrentMeasurement(Measurement *measurement);
};

#endif //PATH_PLANNING_VEHICLE_H
