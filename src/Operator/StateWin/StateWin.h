#ifndef STATE_WIN_H
#define STATE_WIN_H
#include "Operator\StateWin\State.h"
#include "Operator\Mission\Mission.h"
#include "Operator\ProgramPlayer\ProgramPlayer.h"
#include "config.h"

struct Node{
    State state;
    Node* next;
    Node(const State& _state, Node* _next):state(_state), next(_next){};
};

class StateWin
{
    Node* head;
    Node* currentNode;
    Mission* mission;
    DEBUG_PRINT_SERIAL* serial;
    ProgramPlayer PP;
    void deleteStates();
public:
    StateWin();
    StateWin(Mission* _mission, DEBUG_PRINT_SERIAL* serial = nullptr);
    ~StateWin();
    void insert(const State &state);
    void next();
    void reset();
    void loop();
    void printState();
};

#endif