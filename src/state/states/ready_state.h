//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_READY_STATE_H
#define PATH_PLANNING_READY_STATE_H

#include "state.h"

class ReadyState: public State
{
public:
  ReadyState(Controller *controller);

  ~ReadyState();

  void ChangeLaneToLeft(Machine *m);

  void Cruise(Machine *m);

  void ChangeLaneToRight(Machine *m);
};


#endif //PATH_PLANNING_READY_STATE_H
