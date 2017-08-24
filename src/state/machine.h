//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_MACHINE_H
#define PATH_PLANNING_MACHINE_H

#include <vector>
#include "../measurement.h"

class Vehicle;


class Machine
{
  class State *current_;
public:
  class Controller *controller_;

public:
  Machine();
  Machine(Controller *controller);

  Machine(const Machine& source);

  void SetCurrentState(State *state);

  State* GetCurrentState();

  void GetReady();
  
  void Cruise(Vehicle *vehicle);

  void Follow(Vehicle *vehicle);

  void ChangeLaneToLeft(int current_lane);

  void ChangeLaneToRight(int current_lane);

  int GetProposedLane(int current_lane);

  double GetTargetSpeed(Vehicle *vehicle);

  void GoToNextBestState(Vehicle *vehicle);
};

#endif //PATH_PLANNING_MACHINE_H
