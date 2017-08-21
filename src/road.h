//
// Created by Miha Röthl on 20/08/2017.
//

#ifndef PATH_PLANNING_ROAD_H
#define PATH_PLANNING_ROAD_H

class Road {
public:
  int GetLane(double d);

  bool IsLaneAllowed(int lane);

  double GetPreferedSpeedForLane(int lane);

};

#endif //PATH_PLANNING_ROAD_H
