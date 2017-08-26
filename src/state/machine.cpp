//
// Created by Miha Röthl on 14/08/2017.
//
#include "machine.h"

#include <iostream>

#include "states/state.h"
#include "states/ready_state.h"
#include "../cost.h"
#include "../controller.h"

Machine::Machine() {
  this->controller_ = NULL;
  current_ = new ReadyState(this->controller_);
}

Machine::Machine(Controller *controller)
{
  this->controller_ = controller;
  current_ = new ReadyState(this->controller_);
}

Machine::Machine(const Machine& source)
{
  if (source.current_)
  {
    this->current_ = new ReadyState(NULL);
    this->controller_ = NULL;
  }
}

void Machine::SetCurrentState(State *state)
{
  current_ = state;
}

State* Machine::GetCurrentState() {
  return this->current_;
}

void Machine::GetReady() {
  current_->Ready(this, this->controller_);
}

void Machine::Cruise(Vehicle *vehicle){
  this->current_->Cruise(this, this->controller_, vehicle);
}


void Machine::Follow(Vehicle *vehicle) {
  this->current_->Follow(this, this->controller_, vehicle);
}

void Machine::ChangeLaneToLeft(int current_lane) {
  this->current_->ChangeLaneToLeft(this, this->controller_, current_lane);
}

void Machine::ChangeLaneToRight(int current_lane) {
  this->current_->ChangeLaneToRight(this, this->controller_, current_lane);
}

int Machine::GetTargetLane(int current_lane) {
//  std::cout << "proposed:" <<  this->current_->GetProposedLane(current_lane) << std::endl;
  return this->current_->GetProposedLane(current_lane);
}

double Machine::GetTargetSpeed(Vehicle *vehicle) {
  return this->current_->GetTargetSpeed(vehicle);
}

void Machine::GoToNextBestState(Vehicle *vehicle) {
  this->current_->GoToNextBestState(vehicle);
}

