#include "../state.h"

using namespace std;
using namespace state;

Character CharacterFactory::getCharacter(){
  Character newCharacter {};
  newCharacter.job=getJob();
  newCharacter.race=getRace();
  return newCharacter;
}
