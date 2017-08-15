//
// Created by Miha Röthl on 14/08/2017.
//

#include "ready_state.h"

#include <iostream>

#include "cruising_state.h"

using namespace std;

ReadyState::ReadyState() {
  cout << "   ReadyState-ctor  ";
};

ReadyState::~ReadyState() {
  cout << "   ReadyState-dtor\n";
};

void ReadyState::Cruise(Machine *m) {
  cout << "   going to Cruise state\n";
  m->SetCurrentState(new CruisingState());
  delete this;
}
