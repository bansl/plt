#include "../engine.h"
#include "../state/Turn.h"

using namespace engine;
using namespace state;

void Attack::attackAction(state::Character& attackingCharacter,state::Character& defendingCharacter){
  defendingCharacter->setCurrentHP(-attackingCharacter->getAttackPower(attackingCharacter->getRace(),attackingCharacter->getJob(),attackingCharacter->getLevel())+defendingCharacter->getDefense(defendingCharacter->getRace(),defendingCharacter->getJob(),defendingCharacter->getLevel()));
}
