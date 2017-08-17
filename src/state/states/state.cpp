//
// Created by Miha Röthl on 14/08/2017.
//

#include "state.h"

#include <iostream>

using namespace std;

void State::Cruise(Machine *machine){
  throw TransitionNotAllowedException();
}

void State::ChangeLaneToLeft(Machine *machine)
{
  throw TransitionNotAllowedException();
}

void State::ChangeLaneToRight(Machine *machine)
{
  throw TransitionNotAllowedException();
}

void State::Ready(Machine *m)
{
  throw TransitionNotAllowedException();
}

int State::GetProposedLane(int current_lane)
{
  return current_lane;
}