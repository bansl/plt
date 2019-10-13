#include "../state.h"

using namespace state; 
using namespace std;

void Entity::initEntity(){
    this->name="";
    this->position.setPos(0,0);
}

std::string Entity::getName(){
    return name;
}
state::Position Entity::getPosition (){
    return position;
}

state::Tile Entity::getTile (){
    return tile;
}

state::Character Entity::getCharacter(){
    return character;
}

bool Entity::isFree (){
    // TODO
    return true;
}

bool Entity::isCrossable (){
    if(getTile().tile==Water){
        return false;
    }
    else{
        return true;
    }
}