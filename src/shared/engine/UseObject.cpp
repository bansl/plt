#include "../engine.h"

using namespace engine;
using namespace state;

UseObject::UseObject (state::Character& targetCharacter, state::Item object):targetCharacter(targetCharacter),object(object){
    commandType=UseObjectcmd;
}


bool UseObject::action(state::Turn& turn){
  return true;
}


bool UseObject::validate(state::Turn& turn){
  return true;
}