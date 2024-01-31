#include "StateWin.h"
#include "Controller\Controller.h"

StateWin::StateWin(): head(nullptr), currentNode(nullptr) {}

StateWin::StateWin(Mission *_mission, DEBUG_PRINT_SERIAL *serial) : head(nullptr), currentNode(nullptr)
{
    if(_mission != nullptr)
        mission = _mission;
    else{
        if(serial)
            serial->printf("ERROR: Invalid mission pointer");
    }
}

void StateWin::deleteStates(){
    Node* delPointer = head->next;
    while(delPointer != head){
        Node* temp = delPointer->next;
        delete delPointer;
        delPointer = temp;
    }
    delete delPointer;
    head = nullptr;
}

StateWin::~StateWin()
{
    deleteStates();
}

void StateWin::insert(const State& state)
{
    if (head == nullptr){
        head = new Node(state, nullptr);
        head->next = head;
        currentNode = head;
    }
    else{
        currentNode->next = new Node(state, currentNode->next);
        currentNode = currentNode->next;
    }
}

void StateWin::next()
{
    head = head->next;
    PP.reset();
}

void StateWin::reset()
{
    currentNode = head;
}

void StateWin::loop()
{
    currentNode->state.loop(PP.getTime());
}

void StateWin::printState()
{
    if(serial)
        serial->printf("state: %s\n", currentNode->state.getName());
}
