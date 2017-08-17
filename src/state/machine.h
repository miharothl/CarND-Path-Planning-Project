//
// Created by Miha Röthl on 14/08/2017.
//

#ifndef PATH_PLANNING_MACHINE_H
#define PATH_PLANNING_MACHINE_H

class Machine
{
  class State *current_;

public:
  Machine();

  void SetCurrentState(State *state);

  State* GetCurrentState();

  void GetReady();
  
  void Cruise();
 
  void ChangeLaneToLeft();

  void ChangeLaneToRight();

  int GetProposedLane(int current_lane);
};

#endif //PATH_PLANNING_MACHINE_H
