#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;


void Team::viewPartyStats(){


}

void Team::assignPartyStats(){


}

std::vector<Item> Team::getItems (){
    return listItems;
}

void Team::addCharacter(){
  Character character {};
  CharacterFactory cf {};
  character=cf.createCharacter();
  std::unique_ptr<Character> ptr_char (new Character(character));
  listCharacter.push_back(move( ptr_char));
  this->characterNumber+=1;
}

std::vector<std::unique_ptr<Character>>& Team::getListCharacter (){
  std::vector<std::unique_ptr<Character>>& mylistCharacter = listCharacter;
  return mylistCharacter;
}
