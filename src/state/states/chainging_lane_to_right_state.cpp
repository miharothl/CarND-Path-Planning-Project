//
// Created by Miha Röthl on 14/08/2017.
//

#include "chainging_lane_to_right_state.h"

#include <iostream>

#include "cruising_state.h"

using namespace std;

ChaingingLaneToRightState::ChaingingLaneToRightState() {
  cout << "   ChaingingLaneToRightState-ctor ";
}

ChaingingLaneToRightState::~ChaingingLaneToRightState() {
  cout << "   ChaingingLaneToRightState-dtor\n";
}

void ChaingingLaneToRightState::Cruise(Machine *m) {
  cout << "   going to cruising state\n";
  m->SetCurrentState(new CruisingState());
  delete(this);
}
