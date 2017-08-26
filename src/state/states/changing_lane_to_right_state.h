//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_CHAINGING_RIGHT_LEFT_H
#define PATH_PLANNING_CHAINGING_RIGHT_LEFT_H

#include "state.h"

class ChangingLaneToRightState : public State {

public:
  ChangingLaneToRightState(Controller *controller);

  ~ChangingLaneToRightState();

  int GetProposedLane(int current_lane);

  bool IsChangingLanes();

  double CostForState();

  double CostForState(double ego_speed, double traffic_speed);

};

#endif //PATH_PLANNING_CHAINGING_LANE_LEFT_H
