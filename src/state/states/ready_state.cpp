//
// Created by Miha Röthl on 14/08/2017.
//

#include "ready_state.h"

#include <iostream>

#include "cruising_state.h"

using namespace std;

ReadyState::ReadyState(Controller *controller) {
  this->controller_ = controller;
};

ReadyState::~ReadyState() {
}

void ReadyState::ChangeLaneToLeft(Machine *m) {
  State::ChangeLaneToLeft(m, m->controller_);
}

void ReadyState::Cruise(Machine *m) {
  State::Cruise(m, m->controller_);
}

void ReadyState::ChangeLaneToRight(Machine *m) {
  State::ChangeLaneToRight(m, m->controller_);
};

