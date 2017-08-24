//
// Created by Miha Röthl on 20/08/2017.
//

#include "road.h"


#include <cmath>
#include <iostream>

int Road::GetLane(double d) {
  return (int) round( (d-2) / 4);
}

bool Road::IsLaneAllowed(int lane) {
  if ((lane < 0) || (lane > 2)) {
    return false;
  }
  else
  {
    return true;
  }
}

double Road::GetSpeedLimitForLane(int lane) {

  switch (lane)
  {
    case 0:
      return 22.; // m/s
    case 1:
      return 21.; // m/s
    case 2:
      return 20.; // m/s
    default:
      return 10;
  }
}
