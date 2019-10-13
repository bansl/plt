#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 

void ObjectUse::objectUse (state::Team team, state::Item item, state::Entity target){
    std::vector currentItemlist = team.getItems();
    for (size_t i = 0; i < currentItemlist.size; i++)
    {
        if(currentItemlist[i].name == item.name){
            if (currentItemlist[i].quantity>0){
                target.getCharacter().setCurrentHP(currentItemlist[i].getConsumable().healthRestoreAmount);
                target.getCharacter().setCurrentMP(currentItemlist[i].getConsumable().manaRestoreAmount);
                currentItemlist[i].quantity-=1;
            }
        }
    }
    
}