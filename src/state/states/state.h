//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_STATE_H
#define PATH_PLANNING_STATE_H

#include <exception>

#include "../machine.h"
#include "../../controller.h"

class State
{
protected:
  Controller *controller_;

public:
  virtual void Cruise(Machine *machine, Controller *controller, Vehicle *vehicle);

  virtual void Follow(Machine *machine, Controller *controller, Vehicle *vehicle);

  virtual void ChangeLaneToLeft(Machine *machine, Controller *controller, int current_lane);

  virtual void ChangeLaneToRight(Machine *machine, Controller *controller, int current_lane);

  virtual void Ready(Machine *m, Controller *controller);

  virtual int GetProposedLane(int current_lane);

  virtual double CostForState();
  virtual double CostForState(double ego_speed, double traffic_speed);

  virtual bool IsChaingingLanes();

  virtual double GetTargetSpeed(Vehicle* vehicle);

  virtual void GoToNextBestState(Vehicle* vehicle);

private:
  double CalculateCost(Vehicle* vehicle, Machine *cost_machine);
};

class TransitionNotAllowedException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Transition is not implemented in current state.";
  }
};

#endif //PATH_PLANNING_STATE_H
