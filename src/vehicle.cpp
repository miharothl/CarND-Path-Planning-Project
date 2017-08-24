//
// Created by Miha Röthl on 17/08/2017.
//

#include "vehicle.h"

#include <iostream>
#include <cmath>

#include "road.h"

#include "state/machine.h"

using namespace std;

Vehicle::Vehicle(Machine* machine)
{
  this-> machine_ = machine;
  this->current_measurement_ = NULL;

  this-> road_ = new Road();
}

void Vehicle::UpdateEgoData(Measurement *measurement)
{
  this->current_measurement_ = measurement;
}

void Vehicle::UpdateTrafficData(vector<Measurement> measurements)
{
  this->meassurements_ = measurements;
}

int Vehicle::GetLane() {
  if (current_measurement_) {
    double d = this->current_measurement_->D();
    return this->road_->GetLane(d);
  } else {
    return 0;
  }
}

int Vehicle::GetTargetLane() {
  return this->machine_->GetProposedLane(this->GetLane());
}

double Vehicle::GetTargetSpeed() {
  return machine_->GetTargetSpeed(this);
}

void Vehicle::PlanPath()
{
  machine_->GoToNextBestState(this);
}


