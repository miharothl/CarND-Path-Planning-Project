//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_KEEP_LANE_STATE_H
#define PATH_PLANNING_KEEP_LANE_STATE_H

#include "state.h"

class CruisingState: public State
{
public:
  CruisingState();

  ~CruisingState();

  void ChangeLaneToLeft(Machine *m);

  void ChangeLaneToRight(Machine *m);
};

#endif //PATH_PLANNING_KEEP_LANE_STATE_H
