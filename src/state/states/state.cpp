//
// Created by Miha Röthl on 14/08/2017.
//

#include "state.h"

#include <iostream>

#include "../../cost/cost.h"
#include "ready_state.h"
#include "chainging_lane_to_right_state.h"
#include "chainging_lane_to_left_state.h"
#include "cruising_state.h"


using namespace std;

void State::Cruise(Machine *machine, Controller *controller){
  machine->SetCurrentState(new CruisingState(controller));
  delete(this);
}

void State::ChangeLaneToLeft(Machine *machine, Controller *controller)
{
  machine->SetCurrentState(new ChaingingLaneToLeftState(controller));

  delete(this);
}

void State::ChangeLaneToLeft(Machine *machine, Controller *controller, int current_lane) {
  this->ChangeLaneToLeft(machine, controller);

  if (this->controller_ != NULL) {
    this->controller_->lane_ = machine->GetCurrentState()->GetProposedLane(current_lane);
    cout << "controller lane:    " << this->controller_->lane_;
  }
}

void State::ChangeLaneToRight(Machine *machine, Controller *controller)
{
  machine->SetCurrentState(new ChaingingLaneToRightState(controller));
  delete(this);
}

void State::ChangeLaneToRight(Machine *machine, Controller *controller, int current_lane) {
  this->ChangeLaneToRight(machine, controller);

  if (this->controller_ != NULL) {
    this->controller_->lane_ = machine->GetCurrentState()->GetProposedLane(current_lane);
    cout << "controller lane:    " << this->controller_->lane_;
  }
}

void State::Ready(Machine *machine, Controller *controller)
{
  machine->SetCurrentState(new ReadyState(controller));
  delete(this);
}

int State::GetProposedLane(int current_lane)
{
  return current_lane;
}

void State::GoToNextBestState(Vehicle* vehicle)
{
  Cost cost;

  double min_cost = 999999999;
  string best_state = "";

  try {
    Machine cost_machine = *(vehicle->machine_);
    cost_machine.Cruise();
    cost_machine.ChangeLaneToLeft();
    auto cost = this->CalculateCost(vehicle, &cost_machine);

    if (cost < min_cost) {
      best_state = "CLTL";
      min_cost = cost;
    }
  }
  catch (...) {

  }

  try {
    Machine cost_machine = *(vehicle->machine_);
    cost_machine.Cruise();
    auto cost = this->CalculateCost(vehicle, &cost_machine);

    if (cost < min_cost) {
      best_state = "C";
      min_cost = cost;
    }
  }
  catch (...) {

  }

  try {
    Machine cost_machine = *(vehicle->machine_);
    cost_machine.Cruise();
    cost_machine.ChangeLaneToRight();
    auto cost = this->CalculateCost(vehicle, &cost_machine);

    if (cost < min_cost) {
      best_state = "CLTR";
      min_cost = cost;
    }
  }
  catch (...) {

  }

  if (best_state.compare("CLTL") == 0) {
    vehicle->machine_->ChangeLaneToLeft(vehicle->GetLane());

    std::cout << "------------> CHAINGING LANE TO THE LEFT"  << endl;
    return;
  }

  if (best_state.compare("C") == 0 ) {
    vehicle->machine_->Cruise();
    std::cout << "------------> CRUISING"  << endl;
    return;
  }

  if (best_state.compare("CLTR") == 0) {
    vehicle->machine_->ChangeLaneToRight(vehicle->GetLane());
    std::cout << "------------> CHAINGING LANE TO THE RIGHT"  << endl;
    return;
  }
}


double State::CalculateCost(Vehicle* vehicle, Machine *cost_machine) {

  Vehicle cost_vehicle(cost_machine);
  cost_vehicle.UpdateCurrentMeasurement(vehicle->current_measurement_);
  cost_vehicle.UpdateTraffic(vehicle->meassurements_);

  Cost cost;
  return cost.CalculateCost(&cost_vehicle);
}


