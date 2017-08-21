//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_KEEP_LANE_STATE_H
#define PATH_PLANNING_KEEP_LANE_STATE_H

#include "state.h"

#include <vector>

#include "../../vehicle.h"

class CruisingState: public State
{
public:
  CruisingState(Controller *controller);

  ~CruisingState();
};

#endif //PATH_PLANNING_KEEP_LANE_STATE_H
