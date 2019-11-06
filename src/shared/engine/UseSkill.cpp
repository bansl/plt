#include "../engine.h"
#include <iostream>
#include <state.h>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool UseSkill::action(state::Turn& turn){
  for(int i=0;i<(int)targetList.size();i++){
    targetList[i].setCurrentHP(character.getSkillList()[skillNumber]->getHeal()-character.getSkillList()[skillNumber]->getDamage());
  }
  character.setCurrentMP(-character.getSkillList()[skillNumber]->getMpCost());
  return true;
}

UseSkill::UseSkill(state::Character& usedCharacter,std::vector<state::Character>& targetCharacter,int numberSkill):character(usedCharacter),targetList(targetCharacter),skillNumber(numberSkill){
  commandType= UseSkillcmd;
}

bool UseSkill::validate(state::Turn& turn){
  if(character.getStatus()==Available){
    if((int)character.getSkillList().size()>skillNumber){
      if(character.getCurrentMP()>=character.getSkillList()[skillNumber]->getMpCost()){
        character.setStatus(Used);
        return true;
      }
    }
  }
  return false;
}
