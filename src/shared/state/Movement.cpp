#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 
void Movement::movement(Entity character, Position dest){
    Position charPos = character.getCharacter().getPosition();
    int distance = charPos.distanceBetween(charPos,dest);
    if ((distance<5) && character.isFree() && character.isCrossable()){
        charPos.setPos(dest.getX(),dest.getY());
    }
}