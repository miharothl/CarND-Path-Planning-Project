//
// Created by Miha Röthl on 14/08/2017.
//

#include "cruising_state.h"

#include <iostream>
#include <map>

#include "chainging_lane_to_left_state.h"
#include "chainging_lane_to_right_state.h"
#include "../../cost/cost.h"

using namespace std;

CruisingState::CruisingState(Controller *controller) {
  this->controller_ = controller;
};

CruisingState::~CruisingState() {
}

void CruisingState::ChangeLaneToLeft(Machine *m) {
  State::ChangeLaneToLeft(m, m->controller_);
}

void CruisingState::Cruise(Machine *m) {
  State::Cruise(m, m->controller_);
}

void CruisingState::ChangeLaneToRight(Machine *m) {
  State::ChangeLaneToRight(m, m->controller_);
};


