//
// Created by Miha Röthl on 17/08/2017.
//

#include "vehicle.h"

#include <iostream>
#include <cmath>

#include "road.h"

#include "../state/machine.h"

using namespace std;

Vehicle::Vehicle(Machine* machine)
{
  this-> machine_ = machine;

  this-> road_ = new Road();
}

void Vehicle::UpdateCurrentMeasurement(Measurement* measurement)
{
  this->current_measurement_ = measurement;
}

void Vehicle::UpdateTraffic(vector<Measurement> measurements)
{
  this->meassurements_ = measurements;
}

int Vehicle::GetLane() {

  double d = this->current_measurement_->D();
  return this->road_->GetLane(d);
}

int Vehicle::GetProposedLane() {
  return this->machine_->GetProposedLane(this->GetLane());
}

void Vehicle::PlanPath()
{
  machine_->GoToNextBestState(this);
}



