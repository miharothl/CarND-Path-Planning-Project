//
// Created by Miha Röthl on 17/08/2017.
//

#ifndef PATH_PLANNING_VEHICLE_H
#define PATH_PLANNING_VEHICLE_H

#include <vector>
#include <math.h>

#include "measurement.h"
#include "state/machine.h"
#include "road.h"

struct Trajectory {
  std::vector<double> path_x;
  std::vector<double> path_y;
};

class Vehicle {

public:
  Vehicle(Machine* machine);

  Vehicle(Machine* machine, std::vector<double>, std::vector<double>, std::vector<double>);

  int GetLane();

  int GetTargetLane();

  double GetTargetSpeed();

  void UpdateEgoData(Measurement *measurement, bool debug=false);

  void UpdateTrafficData(std::vector<Measurement> measurements);

  void PlanPath();

  Trajectory GetTrajectory(Trajectory previous, double end_path_s);

public:
  Measurement *ego_data_;
  std::vector<Measurement> traffic_data_;

public:
  Machine *machine_;
  Road *road_;
  double ref_vel_;

  std::vector<double> map_waypoints_x_;
  std::vector<double> map_waypoints_y_;
  std::vector<double> map_waypoints_s_;
  constexpr double pi() const { return M_PI; }
  double deg2rad(double x) { return x * pi() / 180; }
  double rad2deg(double x) { return x * 180 / pi(); }

// Transform from Frenet s,d coordinates to Cartesian x,y
  std::vector<double> getXY(double s, double d, std::vector<double> maps_s, std::vector<double> maps_x, std::vector<double> maps_y)
  {
    int prev_wp = -1;

    while(s > maps_s[prev_wp+1] && (prev_wp < (int)(maps_s.size()-1) ))
    {
      prev_wp++;
    }

    int wp2 = (prev_wp+1)%maps_x.size();

    double heading = atan2((maps_y[wp2]-maps_y[prev_wp]),(maps_x[wp2]-maps_x[prev_wp]));
    // the x,y,s along the segment
    double seg_s = (s-maps_s[prev_wp]);

    double seg_x = maps_x[prev_wp]+seg_s*cos(heading);
    double seg_y = maps_y[prev_wp]+seg_s*sin(heading);

    double perp_heading = heading-pi()/2;

    double x = seg_x + d*cos(perp_heading);
    double y = seg_y + d*sin(perp_heading);

    return {x,y};
  }
};

#endif //PATH_PLANNING_VEHICLE_H
