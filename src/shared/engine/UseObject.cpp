#include "../engine.h"
#include <state.h>

using namespace engine;
using namespace state;

UseObject::UseObject (state::Character& targetCharacter, int usedObject,int numberTeam,state::Character& usedChar):character(targetCharacter),object(usedObject),teamNumber(numberTeam),usedCharacter(usedChar){
    commandType=UseObjectcmd;
}


bool UseObject::action(state::Turn& turn){
  turn.getTeams()[teamNumber]->getItems()[object]->modifyQuantity(-1);
  character.setCurrentHP(turn.getTeams()[teamNumber]->getItems()[object]->getConsumable().getHealth());
  character.setCurrentMP(turn.getTeams()[teamNumber]->getItems()[object]->getConsumable().getMana());
  usedCharacter.setStatus(Used);
  return true;
}


bool UseObject::validate(state::Turn& turn){
  if(usedCharacter.getStatus()==Available){
    if(turn.getTeams()[teamNumber]->getItems()[object]->getQuantity()>0){
      usedCharacter.setStatus(UsingObj);
      return true;
    }
    return false;
  }
  return false;
}

bool UseObject::finish(state::Turn& turn){
  usedCharacter.setStatus(Used);
  return true;
}