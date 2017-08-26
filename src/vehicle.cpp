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
  this->machine_ = machine;
  this->ego_data_ = NULL;
  this->road_ = new Road();
}

void Vehicle::UpdateEgoData(Measurement *measurement)
{
  this->ego_data_ = measurement;
}

void Vehicle::UpdateTrafficData(vector<Measurement> measurements)
{
  this->traffic_data_ = measurements;
}

int Vehicle::GetLane() {
  if (ego_data_) {
    double d = this->ego_data_->D();
    return this->road_->GetLane(d);
  } else {
    return 0;
  }
}

int Vehicle::GetTargetLane() {
  return this->machine_->GetTargetLane(this->GetLane());
}

double Vehicle::GetTargetSpeed() {
  return machine_->GetTargetSpeed(this);
}

void Vehicle::PlanPath()
{
  machine_->GoToNextBestState(this);
}


