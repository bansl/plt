#include "../engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool UseSkill::action(state::Turn& turn){
  if((int)character.getSkillList(character.getJob(),character.getLevel()).size()<skillNumber){
    return true;
  }
  else{
    return false;
  }
}

UseSkill::UseSkill(state::Character& usedCharacter,std::vector<std::unique_ptr<state::Character>>& targetCharacter,int numberSkill):character(usedCharacter),targetList(targetCharacter),skillNumber(numberSkill){
  commandType= UseSkillcmd;
}
