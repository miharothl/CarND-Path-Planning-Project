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

