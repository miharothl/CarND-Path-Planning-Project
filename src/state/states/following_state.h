//
// Created by Miha Röthl on 22/08/2017.
//

#ifndef PATH_PLANNING_FOLLOWING_STATE_H
#define PATH_PLANNING_FOLLOWING_STATE_H


#include "../../controller.h"
#include "state.h"

class FollowingState : public State {
public:
  FollowingState(Controller *controller);

  ~FollowingState();

  double GetTargetSpeed(Vehicle* vehicle);

  double CostForState();
};

#endif //PATH_PLANNING_FOLLOWING_STATE_H
