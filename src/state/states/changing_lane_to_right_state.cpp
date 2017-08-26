//
// Created by Miha Röthl on 14/08/2017.
//

#include "changing_lane_to_right_state.h"

#include <iostream>
#include <cmath>

#include "cruising_state.h"
#include "changing_lane_to_left_state.h"

using namespace std;

ChangingLaneToRightState::ChangingLaneToRightState(Controller *controller) {
  this->controller_ = controller;
}

ChangingLaneToRightState::~ChangingLaneToRightState() {
}

int ChangingLaneToRightState::GetProposedLane(int current_lane) {
  return current_lane + 1;
}

bool ChangingLaneToRightState::IsChangingLanes() {
  return true;
}

double ChangingLaneToRightState::CostForState() {

  return -500;
  return 0;
}

double ChangingLaneToRightState::CostForState(double ego_speed, double traffic_speed) {

  if (fabs(ego_speed - traffic_speed) < 2.)
  {
    return +500;
  }
  return 0.;
}

