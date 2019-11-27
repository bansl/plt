#include "../state.h"
#include <iostream>
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

bool Entity::isFree (state::Turn& turn,state::Position tilePos){
    for (size_t i = 0; i < turn.getTeams().size(); i++)
    {
        for (size_t j = 0; j < turn.getTeams()[i]->getListCharacter().size(); j++)
        {
            if((tilePos.distanceBetween(turn.getTeams()[i]->getListCharacter()[j]->getPosition(),tilePos)==0) && (turn.getTeams()[i]->getListCharacter()[j]->getStatus()!=Dead)){
                return false;
            };
        }

    }
    for (size_t k=0;k<turn.getBuffer().size();k++){
      Position pos=*turn.getBuffer()[k];
      if(tilePos.distanceBetween(pos,tilePos)==0){
          return false;
      };
    }
    return true;
}

bool Entity::isCrossable (state::Tile tile){
    if((tile.getTile()==Water) || (tile.getTile()==Pound)) {
        return false;
    }
    else{
        return true;
    }
}