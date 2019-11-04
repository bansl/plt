#include "../engine.h"
#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool Attack::validate (state::Turn& turn){
  if(attacker.getJob().getJob()==Pugilist||attacker.getJob().getJob()==Swordman){
    if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())==1){
      cout<<"attacker pos"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
      cout<<"target pos"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
      cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
      return true;
    }
    else{
      cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
      cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
      cout<<"CAN'T Attack!"<<attacker.getJob().getJob()<<endl;
      return false;
    }
  }
  if(attacker.getJob().getJob()==Magician||attacker.getJob().getJob()==Archer){
    if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())<=4){
      cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
      cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
      cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
      return true;
    }
    else{
      cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
      cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
      cout<<"CAN'T Attack!"<<attacker.getJob().getJob()<<endl;
      return false;
    }
  }
  return false;
}

bool Attack::action(state::Turn& turn){
  
  // defendingCharacter->setCurrentHP(-attackingCharacter->getAttackPower(attackingCharacter->getRace(),attackingCharacter->getJob(),attackingCharacter->getLevel())+defendingCharacter->getDefense(defendingCharacter->getRace(),defendingCharacter->getJob(),defendingCharacter->getLevel()));
}

Attack::Attack (state::Character& attackerCharacter, state::Character& targetCharacter):attacker(attackerCharacter),target(targetCharacter){
    commandType= Attackcmd;
}
