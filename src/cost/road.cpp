//
// Created by Miha Röthl on 20/08/2017.
//

#include "road.h"


#include <cmath>
#include <iostream>

int Road::GetLane(double d) {
  std::cout << "d: " << d;
  std:: cout << "    lane: " << (int) round( (d-2) / 4) << std::endl;
  return (int) round( (d-2) / 4);
}

bool Road::IsLaneAllowed(int lane) {
  if ((lane < 0) || (lane > 3)) {
    return false;
  }
  else
  {
    return true;
  }
}
