#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

int Skill::getHeal(){
  return hpRecovery;
}

int Skill::getDamage(){
  return damage;
}

void Skill::setEffect(int damage, int heal){
  this->damage=damage;
  hpRecovery=heal;
}

void Skill::setMpCost(int newMpCost){
  mpCost=newMpCost;
}

int Skill::getMpCost(){
  return mpCost;
}
