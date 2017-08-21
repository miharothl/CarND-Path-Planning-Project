//
// Created by Miha Röthl on 21/08/2017.
//

#ifndef PATH_PLANNING_CONTROLER_H
#define PATH_PLANNING_CONTROLER_H

#include "road.h"

class Controller {

public:
  Controller(int lane);

  int GetTargetLane();
  void SetTargetLaneAndSpeed(int);

  double GetTargetSpeed();

private:

  Road *road_;

  int lane_;
  double target_speed_;
};


#endif //PATH_PLANNING_CONTROLER_H
