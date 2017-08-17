//
// Created by Miha Röthl on 17/08/2017.
//

#include "vehicle.h"

#include <iostream>
#include <cmath>

#include "../state/machine.h"

Vehicle::Vehicle(Machine* machine)
{
  this-> machine_ = machine;
}

void Vehicle::UpdateCurrentMeasurement(Measurement* measurement)
{
  this->current_measurement_ = measurement;
}

int Vehicle::GetLane() {
  double d = this->current_measurement_->D();
  return (int) round( d / 4);
}

int Vehicle::GetProposedLane() {
  return this->machine_->GetProposedLane(this->GetLane());
}
