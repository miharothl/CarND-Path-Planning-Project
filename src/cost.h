//
// Created by Miha Röthl on 02/08/2017.
//

#ifndef CPP_COST_H
#define CPP_COST_H

#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <iterator>

class Road;
class Vehicle;
struct Snapshot;

struct TrajectoryData {
  int proposed_lane;
  double avg_speed;
  double max_acceleration;
  double rms_acceleration;
  double closest_approach;
  double end_distance_to_goal;
  int end_lanes_from_goal;
  bool collides;
  double collides_at;
};

class Cost {
public:
  Cost();
  ~Cost();

  // priority levels for costs
  double COLLISION  = pow(10, 6);
  double DANGER     = pow(10, 5);
  double REACH_GOAL = pow(10, 5);
  double COMFORT    = pow(10, 4);
  double EFFICIENCY = pow(10, 2);

  double DESIRED_BUFFER = 1.5; //  # timesteps
  double PLANNING_HORIZON = 2;

  // bool DEBUG = False;
  bool DEBUG = true;

  double calculate_cost(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions);

  TrajectoryData get_helper_data(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions);

  std::map<int, std::vector<std::vector<int>>> filter_predictions_by_lane(std::map<int, std::vector<std::vector<int>>> predictions, int lane);

  bool check_collision(Snapshot snapshot, int s_previous, int s_now);

  double change_lane_cost(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data);

  double distance_from_goal_lane_cost(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data);

  double inefficiency_cost(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data);

  double collision_cost(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data);

  double buffer_cost(Vehicle* vehicle, std::vector<Snapshot> trajectory, std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data);
};

#endif
