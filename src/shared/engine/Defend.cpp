#include "../engine.h"
#include <state.h>

using namespace engine;
using namespace state;

bool Defend::action(state::Turn& turn){
  return true;
}

bool Defend::validate(state::Turn& turn){
  if((character.getStatus()==Available) || (character.getStatus()==Moving) ){
    character.setStatus(Defending);
    return true;
  }
  return false;
}

Defend::Defend(state::Character& targetCharacter):character(targetCharacter){
  commandType=Defendcmd;
}

state::Character& Defend::getCharacter(){
  Character & addrCharacter = character;
  return addrCharacter;
}

bool Defend::finish(state::Turn& turn){
  return true;
}

bool Defend::revert(state::Turn& turn){
  character.setStatus(Available);
  return true;
}