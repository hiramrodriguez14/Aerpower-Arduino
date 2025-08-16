#pragma once
#include <iostream>
#include <string>
using namespace std;
class State {
 protected:
  string nextState;
  bool finished = false;

 public:
  virtual void update() = 0;
  virtual void reset() = 0;

  bool hasFinished() { return finished; }
  void setFinished(bool finished) { this->finished = finished; }
  void setNextState(string nextState) { this->nextState = nextState; }
  string getNextState() { return this->nextState; }
};
