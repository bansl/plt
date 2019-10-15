#include "../state.h"

using namespace state;
using namespace std;


void Team::viewPartyStats(){


}

void Team::assignPartyStats(){


}

std::vector<Item> Team::getItems (){
    return listItems;
}

void Team::addCharacter(state::Character character){
  this->listCharacter.push_back(character);
  this->characterNumber+=1;
}
