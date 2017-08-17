//
// Created by Miha Röthl on 14/08/2017.
//

#include "chainging_lane_to_left_state.h"

#include <iostream>

#include "cruising_state.h"

using namespace std;

ChaingingLaneToLeftState::ChaingingLaneToLeftState() {
  cout << "   ChaingingLaneToLeftState-ctor ";
}

ChaingingLaneToLeftState::~ChaingingLaneToLeftState() {
  cout << "   ChaingingLaneToLeftState-dtor\n";
}

void ChaingingLaneToLeftState::Cruise(Machine *m) {
  cout << "   going to cruising state\n";
  m->SetCurrentState(new CruisingState());
  delete(this);
}

int ChaingingLaneToLeftState::GetProposedLane(int current_lane) {
  return current_lane - 1;
}