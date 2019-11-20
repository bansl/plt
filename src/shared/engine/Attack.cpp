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
        attacker.setStatus(Attacking);
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

      Position currentPosition(attacker.getPosition());
      Position newPosition(target.getPosition());
      std::vector<state::Position> neighbors;
      std::vector<state::Position> pathToDest;
      pathToDest={currentPosition};
      bool firstpos=true, notfound=true;
      int iter=0;
      while(notfound && (iter<40)){
          currentPosition.setPos(pathToDest.back().getX()+1,pathToDest.back().getY()  ), neighbors.push_back(currentPosition);
          currentPosition.setPos(pathToDest.back().getX()-1,pathToDest.back().getY()  ), neighbors.push_back(currentPosition);
          currentPosition.setPos(pathToDest.back().getX()  ,pathToDest.back().getY()+1), neighbors.push_back(currentPosition);
          currentPosition.setPos(pathToDest.back().getX()  ,pathToDest.back().getY()-1), neighbors.push_back(currentPosition);
          firstpos=true;
          while(!neighbors.empty()){
              currentPosition.setPos(neighbors.back().getX(),neighbors.back().getY());bool newpos=true;
              for (size_t q = 0; q < pathToDest.size(); q++){
                    if((pathToDest[q].getX()==currentPosition.getX()) && (pathToDest[q].getY()==currentPosition.getY())) newpos=false;
                }
              if(newpos){
                  if(firstpos){
                      pathToDest.push_back(currentPosition);
                      firstpos=false;
                  }
                  else if (currentPosition.distanceBetween(currentPosition,newPosition)<currentPosition.distanceBetween(pathToDest.back(),newPosition)){
                      pathToDest.pop_back();
                      pathToDest.push_back(currentPosition);
                  }
              }
              neighbors.pop_back();
              if(currentPosition.distanceBetween(pathToDest.back(),newPosition)==0){
                  notfound=false;
              }
          }
          iter++;
      }
      int heightModifier=0;
      for(int i=1;i<(int)pathToDest.size();i++){
        heightModifier=std::max(heightModifier,turn.getMap()[pathToDest[i].getX()][pathToDest[i].getY()].getHeight());
      }
      heightModifier=turn.getMap()[pathToDest[0].getX()][pathToDest[0].getY()].getHeight()-heightModifier;
      // cout<<"Range : "<<heightModifier+4<<endl;

      if(attacker.getPosition().distanceBetween(attacker.getPosition(),target.getPosition())<=4+heightModifier){
        // cout<<"attacker pos:"<<attacker.getPosition().getX()<<"|"<< attacker.getPosition().getY() <<endl;
        // cout<<"target pos:"<<target.getPosition().getX()<<"|"<< target.getPosition().getY() <<endl;
        // cout<<"CAN Attack!"<<attacker.getJob().getJob()<<endl;
        attacker.setStatus(Attacking);
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
  attacker.setStatus(Attacking);
  return true;
}

bool Attack::finish(state::Turn& turn){
  attacker.setStatus(Used);
  return true;
}
Attack::Attack (state::Character& attackerCharacter, state::Character& targetCharacter):attacker(attackerCharacter),target(targetCharacter){
    commandType= Attackcmd;
}
