#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

Item::Item(std::string itemName,int health,int mana,int itemQuantity):name(itemName),consumable(Consumable(health,mana)),quantity(itemQuantity){

}

int Item::getQuantity (){
    return quantity;
}

void Item::setQuantity (int newQuantity){
    this->quantity=newQuantity;
}

void Item::modifyQuantity (int quantityModifier){
  this->quantity+=quantityModifier;
}

state::Consumable& Item::getConsumable (){
    Consumable & addrConsumable=consumable;
    return addrConsumable;
}
