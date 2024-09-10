#include "StateWin.h"
#include "Controller\Controller.h"

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

void StateWin::setup(Mission *_mission, DEBUG_PRINT_SERIAL *_serial)
{
    this->serial = _serial;
    this->serial->println("StateWin constructor");
    if(_mission != nullptr)
        mission = _mission;
    else{
        this->serial->printf("ERROR: Invalid mission pointer");
    }
    PP.reset();
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
    this->serial->println("Next!");
    currentNode = currentNode->next;
    PP.reset();
}

void StateWin::reset()
{
    currentNode = head;
}

void StateWin::loop()
{
    if(currentNode)
        currentNode->state.loop(PP.getTime());
}

void StateWin::printState()
{
    if(currentNode){
        this->serial->printf("state: %s\n", currentNode->state.getName());
    }else
        this->serial->println("state: NULL");
}
