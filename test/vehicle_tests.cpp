//
// Created by Miha Röthl on 17/08/2017.
//


#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "../src/measurement.h"
#include "../src/vehicle.h"
#include "../src/state/states/state.h"
#include "../src/state/states/ready_state.h"
#include "../src/state/states/cruising_state.h"
#include "../src/state/states/chainging_lane_to_left_state.h"
#include "../src/state/states/chainging_lane_to_right_state.h"
#include "../src/cost.h"
#include "tools/data.h"

using namespace std;

TEST(vehicle, Should_ReturnCorrectLaneIdentifier_When_MeasurementInLane)
{
  Machine machine;
  Vehicle vehicle(&machine);

  auto ego_measurement_n1 = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , -2.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_n1);
  EXPECT_EQ(-1, vehicle.GetLane());

  auto ego_measurement_0a = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 0.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_0a);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_0b = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 1.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_0b);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_0c = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 2.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_0c);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_0d = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 3.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_0d);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_1 = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 5.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_1);
  EXPECT_EQ(1, vehicle.GetLane());

  auto ego_measurement_2 = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 9.83056 );
  vehicle.UpdateCurrentMeasurement(&ego_measurement_2);
  EXPECT_EQ(2, vehicle.GetLane());
}

TEST(vehicle, Should_BeAbleToPlanPath_When_MeasurementIsGeven) {

  Data data;

//  Controller controller(1);
//  Machine machine(&controller);
  Machine machine;
  machine.Cruise();


  Vehicle vehicle(&machine);
  auto ego_measurement = data.GenerageEgoMeasurement();
  auto traffic_measurement = data.GenerateApproachingTraffic();

  vehicle.UpdateCurrentMeasurement(&ego_measurement);
  vehicle.UpdateTraffic(traffic_measurement);

  vehicle.PlanPath();

  auto proposed = vehicle.GetProposedLane();

  EXPECT_EQ(0, proposed);
}
