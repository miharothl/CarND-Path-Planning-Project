#include <iostream>

#include "gtest/gtest.h"

#include "../src/state/states/state.h"
#include "../src/state/states/ready_state.h"
#include "../src/state/states/cruising_state.h"
#include "../src/state/states/changing_lane_to_left_state.h"
#include "../src/state/states/changing_lane_to_right_state.h"

using namespace std;

TEST(StateMachine, Should_BeInReadyState_When_MachineIsInitialised)
{
  Machine machine;
  auto current_state = machine.GetCurrentState();

  EXPECT_TRUE(typeid(*current_state) == typeid(ReadyState));
  EXPECT_FALSE(typeid(*current_state) == typeid(CruisingState));
}

TEST(StateMachine, Should_ChangeState_When_ChangeStateIsAllowed)
{
  Machine machine;
  Vehicle vehicle(&machine);
  auto current_state = machine.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(ReadyState));

  machine.Cruise(&vehicle);
  current_state = machine.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(CruisingState));

  machine.ChangeLaneToLeft(1);
  current_state = machine.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(ChangingLaneToLeftState));

  machine.Cruise(&vehicle);
  current_state = machine.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(CruisingState));

  machine.ChangeLaneToRight(1);
  current_state = machine.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(ChangingLaneToRightState));
}

TEST(StateMachine, Should_TargetLeftLane_When_InChangingLaneToLeftState)
{
  Machine machine;
  Vehicle vehicle(&machine);
  machine.Cruise(&vehicle);
  machine.ChangeLaneToLeft(1);
  int current_lane = 2;
  int target_lane = machine.GetTargetLane(current_lane);
  EXPECT_EQ(target_lane, current_lane-1);
}

TEST(StateMachine, Should_TargetRightLane_When_InChangingLaneToRightState)
{
  Machine machine;
  Vehicle vehicle(&machine);
  machine.Cruise(&vehicle);
  machine.ChangeLaneToRight(1);
  int current_lane = 2;
  int target_lane = machine.GetTargetLane(current_lane);
  EXPECT_EQ(target_lane, current_lane+1);
}

TEST(StateMachine, Should_TargetSameLane_When_InCruisingState)
{
  Machine machine;
  Vehicle vehicle(&machine);
  machine.Cruise(&vehicle);
  int current_lane = 2;
  int target_lane = machine.GetTargetLane(current_lane);
  EXPECT_EQ(target_lane, current_lane);
}
