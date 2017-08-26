//
// Created by Miha Röthl on 14/08/2017.
//

#include "changing_lane_to_left_state.h"

#include <iostream>

#include "cruising_state.h"
#include "changing_lane_to_right_state.h"

using namespace std;

ChangingLaneToLeftState::ChangingLaneToLeftState(Controller *controller_) {
  this->controller_ = controller_;
}

ChangingLaneToLeftState::~ChangingLaneToLeftState() {
}


int ChangingLaneToLeftState::GetProposedLane(int current_lane) {
  return current_lane - 1;
}

bool ChangingLaneToLeftState::IsChaingingLanes() {
  return true;
}

//void ChangingLaneToLeftState::ChangeLaneToLeft(Machine *m) {
//  State::ChangeLaneToLeft(m, m->controller_);
//}
//
//void ChangingLaneToLeftState::Cruise(Machine *m) {
//  State::Cruise(m, m->controller_);
//}
//
//void ChangingLaneToLeftState::ChangeLaneToRight(Machine *m) {
//  State::ChangeLaneToRight(m, m->controller_);
//}
//
//

