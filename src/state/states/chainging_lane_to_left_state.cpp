//
// Created by Miha Röthl on 14/08/2017.
//

#include "chainging_lane_to_left_state.h"

#include <iostream>

#include "cruising_state.h"
#include "chainging_lane_to_right_state.h"

using namespace std;

ChaingingLaneToLeftState::ChaingingLaneToLeftState(Controller *controller_) {
  this->controller_ = controller_;
}

ChaingingLaneToLeftState::~ChaingingLaneToLeftState() {
}


int ChaingingLaneToLeftState::GetProposedLane(int current_lane) {
  return current_lane - 1;
}

void ChaingingLaneToLeftState::ChangeLaneToLeft(Machine *m) {
  State::ChangeLaneToLeft(m, m->controller_);
}

void ChaingingLaneToLeftState::Cruise(Machine *m) {
  State::Cruise(m, m->controller_);
}

void ChaingingLaneToLeftState::ChangeLaneToRight(Machine *m) {
  State::ChangeLaneToRight(m, m->controller_);
}



