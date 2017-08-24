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
  vehicle.UpdateEgoData(&ego_measurement_n1);
  EXPECT_EQ(-1, vehicle.GetLane());

  auto ego_measurement_0a = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 0.83056 );
  vehicle.UpdateEgoData(&ego_measurement_0a);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_0b = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 1.83056 );
  vehicle.UpdateEgoData(&ego_measurement_0b);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_0c = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 2.83056 );
  vehicle.UpdateEgoData(&ego_measurement_0c);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_0d = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 3.83056 );
  vehicle.UpdateEgoData(&ego_measurement_0d);
  EXPECT_EQ(0, vehicle.GetLane());

  auto ego_measurement_1 = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 5.83056 );
  vehicle.UpdateEgoData(&ego_measurement_1);
  EXPECT_EQ(1, vehicle.GetLane());

  auto ego_measurement_2 = Measurement(-100, 1284.63 , 1187.22 , 22.0218 , -0.799344, 530.087 , 9.83056 );
  vehicle.UpdateEgoData(&ego_measurement_2);
  EXPECT_EQ(2, vehicle.GetLane());
}

TEST(vehicle, Should_BeAbleToStopFollowing_When_CarCouldBeOverTaken) {

  Data data;

//  Controller controller(1);
//  Machine machine(&controller);
  Machine machine;

  Vehicle vehicle(&machine);
  machine.Cruise(&vehicle);

  auto ego_measurement = data.GenerageCase5FollowingEgo();
  auto traffic_measurement = data.GenerateCase5FollowingTraffic();

  vehicle.UpdateEgoData(&ego_measurement);
  vehicle.UpdateTrafficData(traffic_measurement);

  vehicle.PlanPath();

  auto proposed = vehicle.GetTargetLane();

  EXPECT_EQ(1, proposed);
}


TEST(vehicle, Should_BeAbleToPlanPath_When_MeasurementIsGeven) {

  Data data;

//  Controller controller(1);
//  Machine machine(&controller);
  Machine machine;

  Vehicle vehicle(&machine);
  machine.Cruise(&vehicle);

  auto ego_measurement = data.GenerageCase5FollowingEgo();
  auto traffic_measurement = data.GenerateCase5FollowingTraffic();

  vehicle.UpdateEgoData(&ego_measurement);
  vehicle.UpdateTrafficData(traffic_measurement);

  vehicle.PlanPath();

  auto proposed = vehicle.GetTargetLane();

  EXPECT_EQ(1, proposed);
}


TEST(vehicle, Should_AlwaysDriveOnTheRightSideOfTheRoad) {
  Data data;
  Road road;

  auto vehicle = data.GenerateVehicleInTheLeftLaneOfTheEmptyRoad();

  vehicle.PlanPath();

  auto target_lane = vehicle.GetTargetLane();
  auto target_speed = vehicle.GetTargetSpeed();

  EXPECT_EQ(target_lane, data.kLeftLane);
  EXPECT_EQ(target_speed, road.GetSpeedLimitForLane(data.kLeftLane));
}

TEST(vehicle, Should_PreferToDriveInLeftLane_When_ThereIsNoTraffic) {
  Data data;
  Road road;

  auto vehicle = data.GenerateVehicleInTheMiddleLaneOfTheEmptyRoad();

  vehicle.PlanPath();

  auto target_lane = vehicle.GetTargetLane();
  auto target_speed = vehicle.GetTargetSpeed();

  EXPECT_EQ(target_lane, data.kLeftLane);
  EXPECT_EQ(target_speed, road.GetSpeedLimitForLane(data.kLeftLane));
}

TEST(vehicle, Should_OvertakeOnTheLeft_When_ThereIsNoTrafficOnTheLeftLane) {
  Data data;
  Road road;

  auto vehicle = data.GenerateVehicleInTheMiddleLaneFollowingTraffic();

  vehicle.PlanPath();

  auto target_lane = vehicle.GetTargetLane();
  auto target_speed = vehicle.GetTargetSpeed();

  EXPECT_EQ(target_lane, data.kLeftLane);
  EXPECT_EQ(target_speed, road.GetSpeedLimitForLane(data.kLeftLane));
}

TEST(vehicle, Should_OvertakeOnTheRight_When_ThereIsTrafficOnTheLeftLane) {
  Data data;
  Road road;

  auto vehicle = data.GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAhead();

  vehicle.PlanPath();

  auto target_lane = vehicle.GetTargetLane();
  auto target_speed = vehicle.GetTargetSpeed();

  EXPECT_EQ(target_lane, data.kRightLane);
  EXPECT_EQ(target_speed, road.GetSpeedLimitForLane(data.kRightLane));
}

TEST(vehicle, Should_FollowVehicle_When_NotPossibleToOverTakeDueToTraffic) {
  Data data;
  Road road;

  auto vehicle = data.GenerateVehicleInTheMiddleLaneFollowingTrafficAndTrafficOnTheLeftAndRightAhead();

  vehicle.PlanPath();

  auto target_lane = vehicle.GetTargetLane();
  auto target_speed = vehicle.GetTargetSpeed();

  EXPECT_EQ(target_lane, data.kMiddleLane);
  EXPECT_TRUE(target_speed < road.GetSpeedLimitForLane(data.kMiddleLane));
}

TEST(vehicle, Should_FollowVehicle_When_NotPossibleToOverTakeDueToSpeedLimit) {

}

