//
// Created by Miha Röthl on 14/08/2017.
//
#include "machine.h"

#include <iostream>

#include "states/state.h"
#include "states/ready_state.h"

Machine::Machine()
{
  std::cout << '\n';
  current_ = new ReadyState();
}

void Machine::SetCurrentState(State *state)
{
  current_ = state;
}

State* Machine::GetCurrentState() {
  return this->current_;
}

void Machine::GetReady() {
  current_->Ready(this);
}

void Machine::Cruise(){
  this->current_->Cruise(this);
}

void Machine::ChangeLaneToLeft() {
  this->current_->ChangeLaneToLeft(this);
}

void Machine::ChangeLaneToRight() {
  this->current_->ChangeLaneToRight(this);
}

int Machine::GetProposedLane(int current_lane) {
  return this->current_->GetProposedLane(current_lane);
}