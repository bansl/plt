#include "../engine.h"
#include <iostream>
#include <state.h>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool UseSkill::action(state::Turn& turn){
    int damage=character.getSkillList()[skillNumber]->getDamage();
    int heal=character.getSkillList()[skillNumber]->getHeal();
    targetList.setCurrentHP(-damage);
    targetList.setCurrentHP(heal);
    if(remaining==0){
      cout<<character.getSkillList()[skillNumber]->skillName<<"|skill damage: "<<damage<<"|skill heal: "<<heal<<endl;
      character.setCurrentMP(-character.getSkillList()[skillNumber]->getMpCost());
    }
  return true;
}

UseSkill::UseSkill(state::Character& usedCharacter,state::Character& targetCharacter,int numberSkill,int numberRemaining):character(usedCharacter),targetList(targetCharacter),skillNumber(numberSkill),remaining(numberRemaining){
  commandType= UseSkillcmd;
}

bool UseSkill::validate(state::Turn& turn){
  if(character.getStatus()==Available){
    //cout<<"Character is availible"<<endl;
    if((int)character.getSkillList().size()>skillNumber){
      //cout<<"Character has a skill"<<endl;
      if(character.getCurrentMP()>=character.getSkillList()[skillNumber]->getMpCost()){
        //cout<<"Charachter go enough mp to pay mp cost"<<endl;
        if(character.getPosition().distanceBetween(character.getPosition(),targetList.getPosition())<=character.getSkillList()[skillNumber]->getRange()){
          //cout<<"Target character in range of skill"<<endl;
          if(remaining==0){
            //cout<<"Set character status to Attacking"<<endl;
            character.setStatus(Attacking);
            return true;
          }
          else{
            return true;
          }
        }
        else{
          return false;
        }
      }
      else {
        return false;
      }
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
  return false;
}

bool UseSkill::finish(state::Turn& turn){
  character.setStatus(Used);
  return true;
}

engine::Stats& UseSkill::stats(){
  Stats cstats(character,targetList,skillNumber);  
  return cstats;
}
