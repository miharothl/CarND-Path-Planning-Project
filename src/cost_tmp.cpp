//
// Created by Miha Röthl on 02/08/2017.
//

#include "cost_tmp.h"
#include "vehicle_tmp.h"

Cost_tmp::Cost_tmp()
{

}

Cost_tmp::~Cost_tmp()
{

}

double Cost_tmp::buffer_cost(Vehicle_tmp* vehicle, vector<Snapshot> trajectory, map<int, vector<vector<int>>> predictions, TrajectoryData data)
{
  auto closest = data.closest_approach;

  if (closest == 0.)
  {
    return 10 * DANGER;
  }

  auto timestamps_away = closest / data.avg_speed;
  if (timestamps_away > DESIRED_BUFFER)
  {
    return 0.;
  }

  auto multiplier = 1.0 - pow((timestamps_away / DESIRED_BUFFER), 2);
  return multiplier * DANGER;
}

double Cost_tmp::collision_cost(Vehicle_tmp *vehicle, std::vector<Snapshot> trajectory,
                            std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data) {


  auto return_val = 0.;

  if (data.collides) {
    auto time_til_collision = data.collides_at;
    auto exponent = pow(float(time_til_collision), 2);
    auto mult = exp(-exponent);

    return_val = mult * COLLISION;
  }

  cout << "collision_cost: " << return_val << endl;
  return return_val;
}

double Cost_tmp::change_lane_cost(Vehicle_tmp *vehicle, std::vector<Snapshot> trajectory,
                              std::map<int, std::vector<std::vector<int>>> predictions, TrajectoryData data) {

  auto proposed_lanes = data.end_lanes_from_goal;
  auto cur_lanes = trajectory[0].lane;
  auto cost = 0.;
  if (proposed_lanes > cur_lanes) {
    cost = COMFORT;
  }

  if (proposed_lanes < cur_lanes) {
    cost = -COMFORT;
  }

  cout << "change_lane_cost: " << cost << endl;
  return cost;
}

double Cost_tmp::distance_from_goal_lane_cost(Vehicle_tmp *vehicle, std::vector<Snapshot> trajectory,
                                          std::map<int, std::vector<std::vector<int>>> predictions,
                                          TrajectoryData data) {

  auto distance = abs(data.end_distance_to_goal);
  distance = max(distance, 1.0);
  auto time_to_goal = float(distance) / data.avg_speed;
  auto lanes = data.end_lanes_from_goal;
  auto multiplier = float(5 * lanes / time_to_goal);

  auto cost = multiplier * REACH_GOAL;

  cout << "distance_from goal_lane_cost: " << cost << endl;
  return cost;
}

double Cost_tmp::inefficiency_cost(Vehicle_tmp* vehicle, vector<Snapshot> trajectory, map<int, vector<vector<int>>> predictions, TrajectoryData data)
{
  auto speed = data.avg_speed;
  auto target_speed = vehicle->target_speed;
  auto diff = target_speed - speed;
  auto pct = float(diff) / target_speed;
  auto multiplier = pow(pct, 2);


  auto cost = multiplier * EFFICIENCY;
  cout << "inefficiency_cost: " << cost << endl;
  return cost;

}

double Cost_tmp::calculate_cost(Vehicle_tmp* vehicle, vector<Snapshot> trajectory, map<int, vector<vector<int>>> predictions) {

  auto trajectory_data = this->get_helper_data(vehicle, trajectory, predictions);

  cout << "    trajectory_data ->";
  cout << "\n    , proposed_lane: " << trajectory_data.proposed_lane;
  cout << "\n    , end_lanes_from_goal: " << trajectory_data.end_lanes_from_goal;
  cout << "\n    , end_distance_to_goal: " << trajectory_data.end_distance_to_goal;
  cout << "\n    , closest_approach: " << trajectory_data.closest_approach;
  cout << "\n    , avg_speed: " << trajectory_data.avg_speed;
  cout << "\n    , max_acceleration: " << trajectory_data.max_acceleration;
  cout << "\n    , rms_acceleration: " << trajectory_data.rms_acceleration;
  cout << "\n    , collides: " << trajectory_data.collides;
  cout << "\n    , collides_at: " << trajectory_data.collides_at;
  cout << endl;

  auto cost = 0.0;

  cost = cost + this->change_lane_cost(vehicle, trajectory, predictions, trajectory_data);
  cost = cost + this->distance_from_goal_lane_cost(vehicle, trajectory, predictions, trajectory_data);
  cost = cost + this->inefficiency_cost(vehicle, trajectory, predictions, trajectory_data);
  cost = cost + this->collision_cost(vehicle, trajectory, predictions, trajectory_data);
  cost = cost + this->buffer_cost(vehicle, trajectory, predictions, trajectory_data);

  return cost;
}

TrajectoryData Cost_tmp::get_helper_data(Vehicle_tmp* vehicle, std::vector<Snapshot> trajectory,
                                     std::map<int, std::vector<std::vector<int>>> predictions)
{
  auto t = trajectory;
  auto current_snapshot = t[0];
  auto first = t[1];
  auto last = t[t.size() -1 ];
  auto end_distance_to_goal = vehicle->goal_s - last.s;
  auto end_lines_from_goal = abs(vehicle->goal_lane - last.lane);
  auto dt = float(trajectory.size());
  auto proposed_lane = first.lane;
  auto avg_speed = (last.s - current_snapshot.s) / dt;

  // initialize a bunch of variables
  vector<double> accels;
  int closest_apporach = 999999;
  auto collides = false;
  auto collides_at = 999999;
  auto last_snap = trajectory[0];
  auto filtered = this->filter_predictions_by_lane(predictions, proposed_lane);

  for (int i=1; i<PLANNING_HORIZON+1; i++)
  {
    auto snapshot = trajectory[i];
    auto lane = snapshot.lane;
    auto s = snapshot.s;
    auto v = snapshot.v;
    auto a = snapshot.a;

    accels.push_back(a);

    for (auto fp : filtered)
    {
      auto id = fp.first;
      auto state = fp.second[0];
      auto last_state = fp.second[i-1];

      auto vehicle_colides = this->check_collision(snapshot, last_state[1], state[1]);
      if (vehicle_colides) {
        collides = true;
        collides_at = i;
      }

      auto dist = fabs(state[1] - s);
      if (dist < closest_apporach) {
        closest_apporach = dist;
      }
    }
  }

  std::vector<double>::iterator result;
  result = std::max_element(accels.begin(), accels.end());
  auto max_accell = *result;

//  std::vector <int> v1;
//  v1.push_back(1);
//  v1.push_back(2);
//  v1.push_back(3);
//  v1.push_back(4);
//
//  int x = std::inner_product( v1.begin(), v1.end(), v1.begin(), 0 );

  auto sum_sq = std::inner_product( accels.begin(), accels.end(), accels.begin(), 0 );
  auto rms_acceleration = sum_sq / accels.size();

  auto trajectory_data = TrajectoryData();

  trajectory_data.proposed_lane = proposed_lane;
  trajectory_data.avg_speed = avg_speed;
  trajectory_data.max_acceleration = max_accell;
  trajectory_data.rms_acceleration = rms_acceleration;
  trajectory_data.closest_approach = closest_apporach;
  trajectory_data.end_distance_to_goal = end_distance_to_goal;
  trajectory_data.end_lanes_from_goal = end_lines_from_goal;
  trajectory_data.collides = collides;
  trajectory_data.collides_at = collides_at;

  return trajectory_data;
}

bool Cost_tmp::check_collision(Snapshot snapshot, int s_previous, int s_now)
{
  auto s = snapshot.s;
  auto v = snapshot.v;

  auto v_target = s_now - s_previous;

  if (s_previous < s) {
    if (s_now >= s) {
      return true;
    } else {
      return false;
    }
  }

  if (s_previous > s) {
    if (s_now <= s) {
      return true;
    } else {
      return false;
    }
  }

  if (s_previous == s) {
    if (v_target > v) {
      return false;
    } else {
      return true;
    }
  }

  throw std::runtime_error("check collision failed!");
}

std::map<int, vector<vector<int>>> Cost_tmp::filter_predictions_by_lane(map<int, vector<vector<int>>> predictions, int lane)
{
  // TODO:: use copy_if to filter std::map
  map <int, vector<vector<int>>> filtered;

  for (auto vehicle : predictions)
  {
//    cout << vehicle.first << endl;
    if (vehicle.first > 0)
    {
      auto predicted_traj = vehicle.second[0];
      // lane
//      cout << predicted_traj[0] << endl;
      // s
//      cout << predicted_traj[1] << endl;

      if (predicted_traj[0] == lane)
      {
        filtered[vehicle.first] = vehicle.second;
      }
    }
  }

 return filtered;
};