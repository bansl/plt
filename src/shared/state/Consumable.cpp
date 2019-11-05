#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

Consumable::Consumable(int health, int mana):healthRestoreAmount(health),manaRestoreAmount(mana){

}

int Consumable::getHealth(){
  return healthRestoreAmount;
}

int Consumable::getMana(){
  return manaRestoreAmount;
}

void Consumable::setConsumable(int health, int mana){
  healthRestoreAmount=health;
  manaRestoreAmount=mana;
}
