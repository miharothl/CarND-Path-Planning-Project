//
// Created by Miha Röthl on 21/08/2017.
//

#include "controller.h"

#include <iostream>


void Controller::SetTargetLaneAndSpeed(int lane) {
  this->target_lane_ = lane;
  this->target_speed_ = this->road_->GetSpeedLimitForLane(lane);
}

int Controller::GetTargetLane() {
  return target_lane_;
}

Controller::Controller(int lane) {

  this->road_ = new Road();
  this->SetTargetLaneAndSpeed(lane);
}

double Controller::GetTargetSpeed() {
  return target_speed_;
}

void Controller::SetTargetSpeed(double speed) {
  target_speed_ = speed;
}
