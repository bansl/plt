#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;


void Team::viewPartyStats(){


}

void Team::assignPartyStats(){


}

std::vector<std::unique_ptr<Item>>& Team::getItems (){
  std::vector<std::unique_ptr<Item>>& myListItems=listItems;
    return myListItems;
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

void Team::addItem(Item & newItem){
  std::unique_ptr<Item> ptr_newItem (new Item(newItem));
  listItems.push_back(move(ptr_newItem));
}
