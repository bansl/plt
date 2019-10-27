#include "../engine.h"
#include <state.h>

#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

void Move::moveAction(state::Turn& turn){
    if (character.getStatus()==Available){
        if(newPosition.distanceBetween(newPosition,character.getPosition())<10){
            character.getPosition().setPos(newPosition.getX(),newPosition.getY());
        }
    } 
}

Move::Move (state::Character& targetCharacter, state::Position& destination):character(targetCharacter),newPosition(destination){
    commandType= Movecmd;
}