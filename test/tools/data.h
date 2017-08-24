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
  std::vector<Measurement> GenerateApproachingTraffic();
  Measurement GenerageEgoMeasurement();

  std::vector<Measurement> GenerateCase5FollowingTraffic();
  Measurement GenerageCase5FollowingEgo();


  Vehicle GenerateVehicleInTheMiddleLaneOfTheEmptyRoad();
  Vehicle GenerateVehicleInTheLeftLaneOfTheEmptyRoad();
  Vehicle GenerateVehicleInTheMiddleLaneFollowingTraffic();
  Vehicle GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAhead();
  Vehicle GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAndRightAhead();

private:
  Measurement* EgoInTheMiddleLane();
  Measurement* EgoInLeftLane();
  std::vector<Measurement> TrafficNoTraffic();
  std::vector<Measurement> TrafficInTheMiddleLaneAhead();
  std::vector<Measurement> TrafficInTheLeftAndTheMiddleLaneAhead();
  std::vector<Measurement> TrafficInAllLanesAhead();
};


#endif //PATH_PLANNING_DATA_H
