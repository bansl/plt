#include "../state.h"

using namespace state; 
using namespace std;


void Turn::nextTurn (){
    turnNumber+=1;    
}

int Turn::getTurn (){
    return turnNumber;
}

bool Turn::initCursor (){
    ptrCursor=new Cursor();
    return true;
}

state::Cursor* Turn::getCursor (){
    return ptrCursor;
}

std::vector<state::Team> Turn::getTeams (){
    return teams;
}
