#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

std::vector<std::shared_ptr<Item>>& Team::getItems (){
  std::vector<std::shared_ptr<Item>>& myListItems=listItems;
    return myListItems;
}

void Team::addCharacter(){
  Character character {};
  CharacterFactory cf {};
  character=cf.createCharacter();

  std::shared_ptr<Character> ptr_char (new Character(character));
  listCharacter.push_back(ptr_char);
  this->characterNumber+=1;
}

std::vector<std::shared_ptr<Character>>& Team::getListCharacter (){
  std::vector<std::shared_ptr<Character>>& mylistCharacter = listCharacter;
  return mylistCharacter;
}

void Team::addItem(Item & newItem){
  std::shared_ptr<Item> ptr_newItem (new Item(newItem));
  listItems.push_back(ptr_newItem);
}
