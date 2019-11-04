#include "../engine.h"

using namespace engine;

bool Defend::action(state::Turn& turn){
  return true;
}

bool Defend::validate(state::Turn& turn){
  return true;
}

Defend::Defend(state::Character& targetCharacter):character(targetCharacter){
  commandType=Defendcmd;
}
