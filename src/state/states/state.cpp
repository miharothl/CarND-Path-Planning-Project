//
// Created by Miha Röthl on 14/08/2017.
//

#include "state.h"

#include <iostream>

#include "../../cost.h"
#include "ready_state.h"
#include "changing_lane_to_right_state.h"
#include "changing_lane_to_left_state.h"
#include "cruising_state.h"
#include "following_state.h"


using namespace std;

void State::Cruise(Machine *machine, Controller *controller, Vehicle *vehicle){
  machine->SetCurrentState(new CruisingState(controller));

  if (this->controller_ != NULL) {
    this->controller_->SetTargetSpeed(vehicle->GetTargetSpeed());

    cout << "Controller_speed:   " << this->controller_->GetTargetSpeed() << endl;
  }
  delete(this);
}


void State::Follow(Machine *machine, Controller *controller, Vehicle *vehicle) {
  machine->SetCurrentState(new FollowingState(controller));

  if (this->controller_ != NULL) {
    this->controller_->SetTargetSpeed(vehicle->GetTargetSpeed());

    cout << "Controller_speed:   " << this->controller_->GetTargetSpeed() << endl;
  }

  delete(this);
}

void State::ChangeLaneToLeft(Machine *machine, Controller *controller, int current_lane) {
  machine->SetCurrentState(new ChangingLaneToLeftState(controller));

  if (this->controller_ != NULL) {
    this->controller_->SetTargetLaneAndSpeed(machine->GetCurrentState()->GetProposedLane(current_lane));
    cout << "Controller_lane:   " << this->controller_->GetTargetLane() << endl;
  }

  delete(this);
}

void State::ChangeLaneToRight(Machine *machine, Controller *controller, int current_lane) {
  machine->SetCurrentState(new ChangingLaneToRightState(controller));

  if (this->controller_ != NULL) {
    this->controller_->SetTargetLaneAndSpeed(machine->GetCurrentState()->GetProposedLane(current_lane));
    cout << "Controller_lane:   " << this->controller_->GetTargetLane() << endl;
  }

  delete(this);
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
    Vehicle cost_vehicle(&cost_machine);

    cost_vehicle.UpdateEgoData(vehicle->ego_data_);
    cost_vehicle.UpdateTrafficData(vehicle->traffic_data_);

    cost_machine.Cruise(&cost_vehicle);

    Cost cost_computer;
    auto cost = cost_computer.CalculateCost(&cost_vehicle);

    if (cost < min_cost) {
      best_state = "C";
      min_cost = cost;
    }
  }
  catch (...) {

  }


  try {
    Machine cost_machine = *(vehicle->machine_);
    Vehicle cost_vehicle(&cost_machine);

    cost_vehicle.UpdateEgoData(vehicle->ego_data_);
    cost_vehicle.UpdateTrafficData(vehicle->traffic_data_);

    cost_machine.Cruise(&cost_vehicle);
    cost_machine.ChangeLaneToLeft(cost_vehicle.GetLane());

    Cost cost_computer;
    auto cost = cost_computer.CalculateCost(&cost_vehicle);

    if (cost < min_cost) {
      best_state = "CLTL";
      min_cost = cost;
    }
  }
  catch (...) {

  }

  try {
    Machine cost_machine = *(vehicle->machine_);
    Vehicle cost_vehicle(&cost_machine);

    cost_vehicle.UpdateEgoData(vehicle->ego_data_);
    cost_vehicle.UpdateTrafficData(vehicle->traffic_data_);

    cost_machine.Cruise(&cost_vehicle);
    cost_machine.Follow(&cost_vehicle);

    Cost cost_computer;
    auto cost = cost_computer.CalculateCost(&cost_vehicle);

    if (cost < min_cost) {
      best_state = "F";
      min_cost = cost;
    }
  }
  catch (...) {

  }

  try {
    Machine cost_machine = *(vehicle->machine_);
    Vehicle cost_vehicle(&cost_machine);

    cost_vehicle.UpdateEgoData(vehicle->ego_data_);
    cost_vehicle.UpdateTrafficData(vehicle->traffic_data_);

    cost_machine.Cruise(&cost_vehicle);
    cost_machine.ChangeLaneToRight(cost_vehicle.GetLane());

    Cost cost_computer;
    auto cost = cost_computer.CalculateCost(&cost_vehicle);

    if (cost < min_cost) {
      best_state = "CLTR";
      min_cost = cost;
    }
  }
  catch (...) {

  }

  if (best_state.compare("F") == 0) {
    vehicle->machine_->Follow(vehicle);

    std::cout << "------------> FOLLOWING"  << endl;
    return;
  }

  if (best_state.compare("CLTL") == 0) {
    vehicle->machine_->ChangeLaneToLeft(vehicle->GetLane());

    std::cout << "------------> CHANGING LANE TO THE LEFT"  << endl;
    return;
  }

  if (best_state.compare("C") == 0 ) {
    vehicle->machine_->Cruise(vehicle);
    std::cout << "------------> CRUISING"  << endl;
    return;
  }

  if (best_state.compare("CLTR") == 0) {
    vehicle->machine_->ChangeLaneToRight(vehicle->GetLane());
    std::cout << "------------> CHANGING LANE TO THE RIGHT"  << endl;
    return;
  }
}

double State::CalculateCost(Vehicle* vehicle, Machine *cost_machine) {

  Vehicle cost_vehicle(cost_machine);
  cost_vehicle.UpdateEgoData(vehicle->ego_data_);
  cost_vehicle.UpdateTrafficData(vehicle->traffic_data_);

  Cost cost;
  return cost.CalculateCost(&cost_vehicle);
}

double State::GetTargetSpeed(Vehicle *vehicle) {
  Road road;
  return road.GetSpeedLimitForLane(vehicle->GetTargetLane());
}

double State::CostForState() {
  return 0;
}

bool State::IsChangingLanes() {
  return false;
}

double State::CostForState(double ego_speed, double traffic_speed) {
  return 0;
}

void State::LogTrafficAhead(Vehicle *vehicle) {
  cout << "Traffic ahead in lane " << vehicle->GetTargetLane() << endl;
}

void State::LogTrafficOnTheSide(Vehicle *vehicle) {
  cout << "Traffic on the side in lane " << vehicle->GetTargetLane() << endl;
}

void State::LogTrafficBehind(Vehicle *vehicle) {
  cout << "Traffic behind in lane " << vehicle->GetTargetLane() << endl;
}
