//
// Created by Miha Röthl on 17/08/2017.
//

#include <cmath>
#include "measurement.h"

Measurement::Measurement(int id, double x, double y, double vx, double vy, double s, double d) {
  this->id_ = id;
  this->x_ = x;
  this->y_ = y;
  this->vx_ = vx;
  this->vy_ = vy;
  this->s_ = s;
  this-> d_ = d;
}

int Measurement::Id() { return this->id_; }

double Measurement::X() { return this->x_; }

double Measurement::Y() { return this->y_; }

double Measurement::Vx() { return this->vx_; }

double Measurement::Vy() { return this->vy_; }

double Measurement::D() { return this->d_; }

double Measurement::S() { return this->s_; }

double Measurement::V() {
  return sqrt(vx_*vx_ + vy_*vy_);
}

