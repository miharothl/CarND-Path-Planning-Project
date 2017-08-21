//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_KEEP_LANE_STATE_H
#define PATH_PLANNING_KEEP_LANE_STATE_H

#include "state.h"

#include <vector>

#include "../../cost/vehicle.h"

class CruisingState: public State
{
public:
  CruisingState(Controller *controller);

  ~CruisingState();

  void ChangeLaneToLeft(Machine *m);

  void Cruise(Machine *m);

  void ChangeLaneToRight(Machine *m);
};

#endif //PATH_PLANNING_KEEP_LANE_STATE_H
