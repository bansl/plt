#include "../engine.h"

using namespace engine;
using namespace state;

UseObject::UseObject (state::Character& targetCharacter, state::Item object):targetCharacter(targetCharacter),object(object){
    commandType=UseObjectcmd;
}