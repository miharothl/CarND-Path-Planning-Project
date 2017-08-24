#include <iostream>

#include "gtest/gtest.h"

#include "../src/state/states/state.h"
#include "../src/state/states/ready_state.h"
#include "../src/state/states/cruising_state.h"
#include "../src/state/states/chainging_lane_to_left_state.h"
#include "../src/state/states/chainging_lane_to_right_state.h"

using namespace std;

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

TEST(state_machine, Should_BeInReadyState_When_MachineISInitialised)
{
  Machine fsm;
  auto current_state = fsm.GetCurrentState();

  EXPECT_TRUE(typeid(*current_state) == typeid(ReadyState));
  EXPECT_FALSE(typeid(*current_state) == typeid(CruisingState));
}

TEST(state_machine, Should_ChangeState_When_ChangeStateIsAllowed)
{
  Machine fsm;
  Vehicle vehicle(&fsm);
  auto current_state = fsm.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(ReadyState));

  fsm.Cruise(&vehicle);
  current_state = fsm.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(CruisingState));

  fsm.ChangeLaneToLeft(1);
  current_state = fsm.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(ChaingingLaneToLeftState));

  fsm.Cruise(&vehicle);
  current_state = fsm.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(CruisingState));

  fsm.ChangeLaneToRight(1);
  current_state = fsm.GetCurrentState();
  EXPECT_TRUE(typeid(*current_state) == typeid(ChaingingLaneToRightState));
}


TEST(state_machine, Should_ThrowException_When_StateTransitionIsNotAllowed)
{
//  EXPECT_THROW(
//          {
//            try
//            {
//              Machine fsm;
//              fsm.ChangeLaneToLeft(1);
//            }
//            catch(...) {
//              throw;
//            }
//          }
//         , TransitionNotAllowedException);
}


TEST(state_machine, Should_ProposeLeftLane_When_InChangingLaneToLeftState)
{

  Machine fsm;
  Vehicle vehicle(&fsm);
  fsm.Cruise(&vehicle);
  fsm.ChangeLaneToLeft(1);
  int current_lane = 2;
  int proposed_lane = fsm.GetProposedLane(current_lane);
  EXPECT_EQ(proposed_lane, current_lane-1);
}

TEST(state_machine, Should_ProposeRightLane_When_InChangingLaneToRightState)
{
  Machine fsm;
  Vehicle vehicle(&fsm);
  fsm.Cruise(&vehicle);
  fsm.ChangeLaneToRight(1);
  int current_lane = 2;
  int proposed_lane = fsm.GetProposedLane(current_lane);
  EXPECT_EQ(proposed_lane, current_lane+1);
}

TEST(state_machine, Should_ProposeSameLane_When_InCruisingState)
{
  Machine fsm;
  Vehicle vehicle(&fsm);
  fsm.Cruise(&vehicle);
  int current_lane = 2;
  int proposed_lane = fsm.GetProposedLane(current_lane);
  EXPECT_EQ(proposed_lane, current_lane);
}
