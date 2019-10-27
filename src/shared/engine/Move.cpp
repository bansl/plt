#include "../engine.h"
#include "../state/Turn.h"

using namespace engine;
using namespace state;

void Move::moveAction(state::Character& character,state::Position newPosition){
  character->getPosition().setX(newPosition.getX());
  character->getPosition().setY(newPosition.getY());
}
