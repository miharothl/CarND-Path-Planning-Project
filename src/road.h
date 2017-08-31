//
// Created by Miha Röthl on 20/08/2017.
//

#ifndef PATH_PLANNING_ROAD_H
#define PATH_PLANNING_ROAD_H

class Road {

public:
  int GetLane(double d);

  bool IsLaneOnTheRoad(int lane);

  double GetPreferredSpeedForLane(int lane);

private:
  const double lane_width_ = 4.; // meters

  const double speed_limit_ = 22.; // m/s

  const double left_lane_ = 0;

  const double middle_lane_ = 1;

  const double right_lane_ = 2;
};

#endif //PATH_PLANNING_ROAD_H
