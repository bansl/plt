#include "../engine.h"

using namespace engine;
using namespace state;

UseObject::UseObject (state::Character& targetCharacter, int usedObject,int numberTeam):character(targetCharacter),object(usedObject),teamNumber(numberTeam){
    commandType=UseObjectcmd;
}


bool UseObject::action(state::Turn& turn){
  turn.getTeams()[teamNumber]->getItems()[object].quantity+=-1;
  character.setCurrentHP(turn.getTeams()[teamNumber]->getItems()[object].getConsumable().healthRestoreAmount);
  character.setCurrentMP(turn.getTeams()[teamNumber]->getItems()[object].getConsumable().manaRestoreAmount);
  return true;
}


bool UseObject::validate(state::Turn& turn){
  if(turn.getTeams()[teamNumber]->getItems()[object].quantity>0){
    return true;
  }
  return false;
}
