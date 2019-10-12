#include "../state.h"

using namespace state; 
using namespace std;

void Position::setX(int newX){
    this->xPos=newX;
}

void Position::setY(int newY){
    this->yPos=newY;
}

int Position::getX(){
    return xPos;
}

int Position::getY(){
    return yPos;
}

int Position::distanceBetween(state::Position pos1, state::Position pos2){
    return abs(pos1.getX()-pos2.getX())+abs(pos1.getY()-pos2.getY());
}

void Position::setPos(int newX, int newY){
    this->xPos=newX;
    this->yPos=newY;
}

