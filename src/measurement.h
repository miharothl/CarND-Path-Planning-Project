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

public:
  Measurement(int id, double x, double y, double vx, double vy, double s, double d);

  int Id();
  double X();
  double Y();
  double Vx();
  double Vy();
  double S();
  double D();
};

#endif //PATH_PLANNING_MEASUREMENT_H
