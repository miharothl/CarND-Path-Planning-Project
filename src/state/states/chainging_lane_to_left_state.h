//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_CHAINGING_LANE_LEFT_H
#define PATH_PLANNING_CHAINGING_LANE_LEFT_H

#include "state.h"

class ChaingingLaneToLeftState : public State {

public:
  ChaingingLaneToLeftState();

  ~ChaingingLaneToLeftState();

  void Cruise(Machine *m);
};

#endif //PATH_PLANNING_CHAINGING_LANE_LEFT_H
