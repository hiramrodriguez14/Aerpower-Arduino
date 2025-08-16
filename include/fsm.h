#include <iostream>
#include <string>
using namespace std;

class State {

    protected:
        string nextState;
        
public:
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual std::string getName() = 0;
};

class StateMachine {
public:
    void changeState(State* newState) {
        if (currentState) {
            currentState->exit();
        }
        currentState = newState;
        if (currentState) {
            currentState->enter();
        }
    }

private:
    State* currentState = nullptr;
};
