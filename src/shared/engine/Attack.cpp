#include "../engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool Attack::attackAction(){
  if(attacker.getJob().getJob()==Pugilist||attacker.getJob().getJob()==Swordman){
    if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())==1){
      cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
      return true;
    }
    else{
      cout<<"CAN'T Attack!"<<attacker.getJob().getJob()<<endl;
      return false;
    }
  }
  if(attacker.getJob().getJob()==Magician||attacker.getJob().getJob()==Archer){
    if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())<=4){
      cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
      return true;
    }
    else{
      cout<<"CAN'T Attack!"<<attacker.getJob().getJob()<<endl;
      return false;
    }
  }
  return false;
  // defendingCharacter->setCurrentHP(-attackingCharacter->getAttackPower(attackingCharacter->getRace(),attackingCharacter->getJob(),attackingCharacter->getLevel())+defendingCharacter->getDefense(defendingCharacter->getRace(),defendingCharacter->getJob(),defendingCharacter->getLevel()));
}

Attack::Attack (state::Character& attackerCharacter, state::Character& targetCharacter):attacker(attacker),target(targetCharacter){
    commandType= Attackcmd;
}
