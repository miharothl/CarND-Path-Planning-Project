//
// Created by Miha Röthl on 14/08/2017.
//

#include "chainging_lane_to_right_state.h"

#include <iostream>

#include "cruising_state.h"
#include "chainging_lane_to_left_state.h"

using namespace std;

ChaingingLaneToRightState::ChaingingLaneToRightState(Controller *controller) {
  this->controller_ = controller;
}

ChaingingLaneToRightState::~ChaingingLaneToRightState() {
}

int ChaingingLaneToRightState::GetProposedLane(int current_lane) {
  return current_lane + 1;
}

bool ChaingingLaneToRightState::IsChaingingLanes() {
  return true;
}
