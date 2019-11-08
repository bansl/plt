#include "../engine.h"
#include <iostream>
#include <unistd.h>
#include <state.h>

using namespace engine;
using namespace state;
using namespace std;

bool Attack::validate (state::Turn& turn){
  //int height=0;
  // int x=attacker.getPosition().getX(), y=attacker.getPosition().getY();
  // std::vector<std::vector<state::Tile>> map=turn.getMap();
  // Tile tile=map[x][y];
  // height=tile.getHeight();
  if (attacker.getStatus()==Available){
    if(attacker.getJob().getJob()==Pugilist||attacker.getJob().getJob()==Swordman){
      if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())==1){
        // cout<<"attacker pos"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
        // cout<<"target pos"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
        // cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
        attacker.setStatus(Used);
        return true;
      }
      else{
        // cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
        // cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
        // cout<<"CAN'T Attack!"<<attacker.getJob().getJob()<<endl;
        return false;
      }
    }
    if(attacker.getJob().getJob()==Magician||attacker.getJob().getJob()==Archer){
      if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())<=2+height){
        // cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
        // cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
        // cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
        attacker.setStatus(Used);
        return true;
      }
      else{
        // cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
        // cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
        // cout<<"CAN'T Attack!"<<attacker.getJob().getJob()<<endl;
        return false;
      }
    }
  }
  return false;
}

bool Attack::action(state::Turn& turn){
  if(attacker.getAttackPower()>target.getDefense()){
    target.setCurrentHP(-attacker.getAttackPower()+target.getDefense());
  }
  return true;
}

Attack::Attack (state::Character& attackerCharacter, state::Character& targetCharacter, int attackerHeight):attacker(attackerCharacter),target(targetCharacter),height(attackerHeight){
    commandType= Attackcmd;
}
