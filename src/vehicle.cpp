//
// Created by Miha Röthl on 17/08/2017.
//

#include "vehicle.h"

#include <iostream>
#include <cmath>

#include "road.h"

#include "state/machine.h"
#include "lib/spline.h"

using namespace std;

Vehicle::Vehicle(Machine* machine)
{
  this->machine_ = machine;
  this->ego_data_ = NULL;
  this->road_ = new Road();
  this->ref_vel_ = 0.;
}

Vehicle::Vehicle(Machine *machine, std::vector<double> map_waypoints_x, std::vector<double> map_waypoints_y, std::vector<double> map_waypoints_s) {
  this->machine_ = machine;
  this->ego_data_ = NULL;
  this->road_ = new Road();
  this->ref_vel_ = 0.;

  this->map_waypoints_x_ = map_waypoints_x;
  this->map_waypoints_y_ = map_waypoints_y;
  this->map_waypoints_s_ = map_waypoints_s;
}

void Vehicle::UpdateEgoData(Measurement *measurement, bool debug)
{
  this->ego_data_ = measurement;

  if (debug) {
    cout << "---------------------------------\n";
    cout << "car EGO ";
    cout << "; x: " << ego_data_->X();
    cout << "; y: " << ego_data_->Y();
    cout << "; vx: " << ego_data_->Vx();
    cout << "; vy: " << ego_data_->Vy();
    cout << "; s: " << ego_data_->S();
    cout << "; d: " << ego_data_->D();
    cout << "; speed: " << ego_data_->V();
    cout << "; yaw: " << ego_data_->Yaw() ;
    cout << endl;
  }
}

void Vehicle::UpdateTrafficData(vector<Measurement> measurements)
{
  this->traffic_data_ = measurements;
}

int Vehicle::GetLane() {
  if (ego_data_) {
    double d = this->ego_data_->D();
    return this->road_->GetLane(d);
  } else {
    return 0;
  }
}

int Vehicle::GetTargetLane() {
  return this->machine_->GetTargetLane(this->GetLane());
}

double Vehicle::GetTargetSpeed() {
  return machine_->GetTargetSpeed(this);
}

void Vehicle::PlanPath()
{
  machine_->GoToNextBestState(this);
}

Trajectory Vehicle::GenerateTrajectory(Trajectory prev, double end_path_s) {

  int prev_size = prev.path_x.size();

  double car_s = ego_data_->S();
  if (prev_size > 0)
  {
    car_s = end_path_s;
  }

  if (ref_vel_ < this->GetTargetSpeed())
  {
    ref_vel_ += .17;
  }
  else if (ref_vel_ > this->GetTargetSpeed())
  {
    ref_vel_ -= .17;
  }

  // Create a list of widely spaced (x.y) waypoints, evenly spaced at 30m
  vector<double> ptsx;
  vector<double> ptsy;

  // Reference x, y, yaw states
  double ref_x = ego_data_->X();
  double ref_y = ego_data_->Y();
  double ref_yaw = deg2rad(ego_data_->Yaw());

  // If previous size is almost empty use the car as starting reference
  if (prev_size < 2) {
    // Use two points that make the path tangent to the car
    double prev_car_x = ego_data_->X() - cos(ego_data_->Yaw());
    double prev_car_y = ego_data_->Y() - sin(ego_data_->Yaw());

    ptsx.push_back(prev_car_x);
    ptsx.push_back(ego_data_->X());

    ptsy.push_back(prev_car_y);
    ptsy.push_back(ego_data_->Y());
  }
  else
  {
    ref_x = prev.path_x[prev_size-1];
    ref_y = prev.path_y[prev_size-1];

    double ref_x_prev = prev.path_x[prev_size-2];
    double ref_y_prev = prev.path_y[prev_size-2];

    ref_yaw = atan2(ref_y-ref_y_prev, ref_x-ref_x_prev);

    ptsx.push_back(ref_x_prev);
    ptsx.push_back(ref_x);

    ptsy.push_back(ref_y_prev);
    ptsy.push_back(ref_y);
  }

  int lane = GetTargetLane();
  // In Frenet add evenly 30m spaced points ahead of the starting reference
  vector<double> next_wp0 = getXY(car_s+30, 2+4*lane, map_waypoints_s_, map_waypoints_x_, map_waypoints_y_);
  vector<double> next_wp1 = getXY(car_s+60, 2+4*lane, map_waypoints_s_, map_waypoints_x_, map_waypoints_y_);
  vector<double> next_wp2 = getXY(car_s+90, 2+4*lane, map_waypoints_s_, map_waypoints_x_, map_waypoints_y_);

  ptsx.push_back(next_wp0[0]);
  ptsx.push_back(next_wp1[0]);
  ptsx.push_back(next_wp2[0]);

  ptsy.push_back(next_wp0[1]);
  ptsy.push_back(next_wp1[1]);
  ptsy.push_back(next_wp2[1]);

  for (int i=0; i<ptsx.size(); i++) {
    // shift car reference angle to 0 degrees
    double shift_x = ptsx[i] - ref_x;
    double shift_y = ptsy[i] - ref_y;

    ptsx[i] = (shift_x * cos(0-ref_yaw)-shift_y*sin(0-ref_yaw));
    ptsy[i] = (shift_x * sin(0-ref_yaw)+shift_y*cos(0-ref_yaw));
  }

  // Create a spline
  tk::spline s;

  // set (x,y) points to the spline
  s.set_points(ptsx, ptsy);

  Trajectory next;

  // Start with all the previous path points from last time
  for (int i=0; i<prev.path_x.size(); i++) {
    next.path_x.push_back(prev.path_x[i]);
    next.path_y.push_back(prev.path_y[i]);
  }

  double target_x = 30.0;
  double target_y = s(target_x);
  double target_dist = sqrt(target_x*target_x + target_y*target_y);

  double x_add_on = 0;

  // Fill up the rest of our path planner after filling it with previous points, here we will always output 50 points
  for (int i=1; i<=50-prev.path_x.size(); i++) {

    double N = (target_dist/(.02*ref_vel_));
    double x_point = x_add_on + (target_x) / N;
    double y_point = s(x_point);

    x_add_on = x_point;

    double x_ref = x_point;
    double y_ref = y_point;

    //rotate back to world coordinates
    x_point = (x_ref * cos(ref_yaw)-y_ref*sin(ref_yaw));
    y_point = (x_ref * sin(ref_yaw)+y_ref*cos(ref_yaw));

    x_point += ref_x;
    y_point += ref_y;

    next.path_x.push_back(x_point);
    next.path_y.push_back(y_point);
  }

  return next;
}



