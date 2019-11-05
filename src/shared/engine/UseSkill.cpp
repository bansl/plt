#include "../engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool UseSkill::action(state::Turn& turn){
  for(int i=0;i<(int)targetList.size();i++){
    targetList[i]->setCurrentHP(character.getSkillList(character.getJob(),character.getLevel())[skillNumber].hpRecovery-character.getSkillList(character.getJob(),character.getLevel())[skillNumber].damage);
  }
  character.setCurrentMP(-character.getSkillList(character.getJob(),character.getLevel())[skillNumber].mpCost);
  return true;
}

UseSkill::UseSkill(state::Character& usedCharacter,std::vector<std::unique_ptr<state::Character>>& targetCharacter,int numberSkill):character(usedCharacter),targetList(targetCharacter),skillNumber(numberSkill){
  commandType= UseSkillcmd;
}

bool UseSkill::validate(state::Turn& turn){
  if((int)character.getSkillList(character.getJob(),character.getLevel()).size()<skillNumber){
    if(character.getCurrentMP()>=character.getSkillList(character.getJob(),character.getLevel())[skillNumber].mpCost){
      return true;
    }
  }
  return false;
}
