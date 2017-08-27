//
// Created by Miha Röthl on 17/08/2017.
//

#ifndef PATH_PLANNING_MEASUREMENT_H
#define PATH_PLANNING_MEASUREMENT_H

class Measurement {
  int id_;
  double x_;
  double y_;
  double vx_;
  double vy_;
  double s_;
  double d_;
  double yaw_;

public:
  Measurement(int id, double x, double y, double vx, double vy, double s, double d);
  Measurement(int id, double x, double y, double vx, double vy, double s, double d, double yaw);

  int Id();
  double X();
  double Y();
  double Vx();
  double Vy();
  double S();
  double D();
  double Yaw();

  double V();
};

#endif //PATH_PLANNING_MEASUREMENT_H
