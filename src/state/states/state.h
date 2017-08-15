//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_STATE_H
#define PATH_PLANNING_STATE_H

#include <exception>

#include "../machine.h"

class State
{
public:
  virtual void Cruise(Machine *machine);

  virtual void ChangeLaneToLeft(Machine *machine);

  virtual void ChangeLaneToRight(Machine *machine);

  virtual void ready(Machine *m);
};

class TransitionNotAllowedException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Transition is not implemented in current state.";
  }
};

#endif //PATH_PLANNING_STATE_H
