//
// Created by Miha Röthl on 14/08/2017.
//

#include "state.h"

#include <iostream>

using namespace std;

void State::Cruise(Machine *machine){
  throw TransitionNotAllowedException();
  cout << "   already cruising\n";
}

void State::ChangeLaneToLeft(Machine *machine)
{
  throw TransitionNotAllowedException();
  cout << "   already changing lane to the left\n";
}

void State::ChangeLaneToRight(Machine *machine)
{
  throw TransitionNotAllowedException();
  cout << "   already changing lane to the right\n";
}

void State::ready(Machine *m)
{
  throw TransitionNotAllowedException();
  cout << "   already ready\n";
}