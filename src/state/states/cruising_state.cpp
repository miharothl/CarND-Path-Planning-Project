//
// Created by Miha Röthl on 14/08/2017.
//

#include "cruising_state.h"

#include <iostream>

#include "chainging_lane_to_left_state.h"
#include "chainging_lane_to_right_state.h"

using namespace std;

CruisingState::CruisingState() {
  cout << "   CruisingState-ctor ";
};

CruisingState::~CruisingState() {
  cout << "   CruisingState-dtor\n";
};

void CruisingState::ChangeLaneToLeft(Machine *m)
{
  cout << "   going to changing_lane_to_left state\n";
  m->SetCurrentState(new ChaingingLaneToLeftState());
  delete this;
}

void CruisingState::ChangeLaneToRight(Machine *m)
{
  cout << "   going to changing_lane_to_right state\n";
  m->SetCurrentState(new ChaingingLaneToRightState());
  delete this;
}
