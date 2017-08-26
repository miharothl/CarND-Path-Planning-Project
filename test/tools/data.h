//
// Created by Miha Röthl on 20/08/2017.
//

#ifndef PATH_PLANNING_DATA_H
#define PATH_PLANNING_DATA_H

#include <vector>

#include "../../src/measurement.h"
#include "../../src/vehicle.h"

class Data {

public:
  const int kLeftLane = 0;
  const int kMiddleLane = 1;
  const int kRightLane = 2;

public:
  Vehicle GenerateVehicleInTheMiddleLaneOfTheEmptyRoad();
  Vehicle GenerateVehicleInTheLeftLaneOfTheEmptyRoad();
  Vehicle GenerateVehicleInTheMiddleLaneFollowingTraffic();
  Vehicle GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAhead();
  Vehicle GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAndRightAhead();
  Vehicle GenerateVehicleInTheLeftLaneFollowingFastTraffic();
  Vehicle GenerateVehicleInRealScenario();

private:
  Measurement* EgoInTheMiddleLane();
  Measurement* EgoInLeftLane();
  Measurement* EgoInTheLeftLaneGoingFast();
  Measurement* EgoInRealScenario();

  std::vector<Measurement> TrafficNoTraffic();
  std::vector<Measurement> TrafficInTheMiddleLaneAhead();
  std::vector<Measurement> TrafficInTheLeftAndTheMiddleLaneAhead();
  std::vector<Measurement> TrafficInAllLanesAhead();
  std::vector<Measurement> TrafficInTheLeftLaneAheadGoingFast();
  std::vector<Measurement> TrafficInRealScenario();
};

#endif //PATH_PLANNING_DATA_H
