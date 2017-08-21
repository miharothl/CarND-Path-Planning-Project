//
// Created by Miha Röthl on 20/08/2017.
//

#ifndef PATH_PLANNING_DATA_H
#define PATH_PLANNING_DATA_H


#include <vector>

#include "../../src/sensor/measurement.h"

class Data {
public:
  std::vector<Measurement> GenerateApproachingTraffic();
  Measurement GenerageEgoMeasurement();

};


#endif //PATH_PLANNING_DATA_H
