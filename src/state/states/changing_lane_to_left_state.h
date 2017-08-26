//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_CHAINGING_LANE_LEFT_H
#define PATH_PLANNING_CHAINGING_LANE_LEFT_H

#include "state.h"

class ChangingLaneToLeftState : public State {

public:
  ChangingLaneToLeftState(Controller *controller);

  ~ChangingLaneToLeftState();

  int GetProposedLane(int current_lane);

  bool IsChaingingLanes();
};

#endif //PATH_PLANNING_CHAINGING_LANE_LEFT_H
