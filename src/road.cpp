//
// Created by Miha Röthl on 20/08/2017.
//

#include "road.h"


#include <cmath>
#include <iostream>

int Road::GetLane(double d) {
  return (int) round( (d-lane_width_/2) / lane_width_);
}

bool Road::IsLaneOnTheRoad(int lane) {
  if ((lane < left_lane_) || (lane > right_lane_))
  {
    return false;
  }
  else
  {
    return true;
  }
}

double Road::GetPreferredSpeedForLane(int lane) {

  switch (lane)
  {
    case 0:
      return this->speed_limit_;
    case 1:
      return speed_limit_ * 0.95;
    case 2:
      return speed_limit_ * 0.9;
    default:
      return 5; // m/s
  }
}
